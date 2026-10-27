# Lesson 02: Arrays & Memory Layout

> **Phase:** 0 · **Section:** 01 · **Estimated time:** 2–3 hours

## 🎯 Lesson Goal
Understand what an **array** really is at the memory level: a block of same-type
values laid out side by side, where indexing (`arr[i]`) is nothing more than
**pointer arithmetic**. By the end you can compute the address of any element by
hand, explain why `arr[i]` and `*(arr + i)` are the same thing, and state — at
the byte level — why arrays are the root cause of **buffer overflows**.

## 🧩 Prerequisite
Lesson 01 (Pointers). You must already be comfortable with: **address** (the
numeric label of a memory box), `&x` (take the address of `x`), and `*p`
(dereference — go to the address in `p` and read/write the value there). If any
of those feel shaky, re-read lesson-01 or ask Claude to re-explain before
continuing.

---

## 📖 Explanation

### Where this lesson sits on the road

```
 lesson-01-pointers   →   [ THIS LESSON ]   →   lesson-03+ (buffer overflow)
   "an address is          lesson-02:            "write past the end,
    just a number"          ARRAYS                corrupt the neighbour"
```

Lesson 01 gave you one box and its address. This lesson lines up **many boxes in
a row** — and shows that the array is really just pointers wearing a friendlier
costume.

### An array = many same-type boxes, back to back

> **Array:** a fixed-size, ordered collection of elements that are **all the
> same type**, stored in **one continuous block** of memory — one element right
> after another, with **no gaps**.

New terms, explained on first use:

- **Element** — one single value inside the array (one "box" / one slot).
- **Index** — the position number of an element. In C, counting **starts at 0**,
  so the first element is `arr[0]`, not `arr[1]`.
- **Contiguous** — placed directly next to each other in memory, back-to-back.
- **Element size** — how many **bytes** one element occupies, decided by the
  type: `char` = 1 byte, `int` = 4 bytes (on the platforms we target).

```c
int numbers[4] = {10, 20, 30, 40};
```

This means: *reserve one block big enough for 4 integers, place them side by
side, and fill them with 10, 20, 30, 40.*

### The base address

The address of the **whole block** is the address of its **first element**:

```
 base address of the array  ==  &numbers[0]  ==  the value of `numbers` itself
```

Keep this in mind — it's the hinge of the whole lesson.

### 🖼️ Diagram

Each `int` is 4 bytes. Say the block starts (its **base address**) at `0x1000`:

```
            int numbers[4] = {10, 20, 30, 40};

 index:        [0]          [1]          [2]          [3]
             +--------+   +--------+   +--------+   +--------+
 value:      |   10   |   |   20   |   |   30   |   |   40   |
             +--------+   +--------+   +--------+   +--------+
 address:    0x1000       0x1004       0x1008       0x100C
             \______/     \______/     \______/     \______/
              4 bytes      4 bytes      4 bytes      4 bytes

 base = 0x1000  ==  &numbers[0]  ==  numbers
```

The addresses jump by **4** each time, because each element is **4 bytes** wide.
That jump size — the element size — is the key to everything below.

A `char` array (1 byte each) jumps by **1**:

```
            char name[4] = {'P','W','N', 0};
                                        ^ the 0 is the null terminator \0

 index:        [0]      [1]      [2]      [3]
             +-----+  +-----+  +-----+  +-----+
 value:      | 'P' |  | 'W' |  | 'N' |  |  0  |
             +-----+  +-----+  +-----+  +-----+
 address:    0x2000   0x2001   0x2002   0x2003
```

> **Null terminator (`\0`, the byte value 0):** marks the **end of a C string**.
> Functions like `strlen` and `strcpy` keep reading bytes until they hit this 0.
> Remember it — it becomes critical in string overflows later.

### The core formula (address of any element)

To find the address of element `i`:

```
 address_of( arr[i] )  =  base_address  +  ( i  ×  element_size )
```

Worked example with `int numbers[4]` at base `0x1000`, element size 4:

```
 numbers[0]  →  0x1000 + (0 × 4)  =  0x1000
 numbers[1]  →  0x1000 + (1 × 4)  =  0x1004
 numbers[2]  →  0x1000 + (2 × 4)  =  0x1008
 numbers[3]  →  0x1000 + (3 × 4)  =  0x100C
```

(`0x1008 + 4 = 0x100C`, because in hexadecimal `8 + 4 = C`.) This is exactly
what the CPU computes every time you write `numbers[i]`. The index is **not** a
magic label — it's a **multiplier** inside an addition.

### Why `arr[i]` is the same as `*(arr + i)`

In C, when you use the array name `arr` in an expression, it **decays** into the
**address of its first element**. So `arr` by itself means `0x1000` in our
example.

> **Decay:** C automatically treats an array name as a pointer to element 0 in
> most expressions. This is the bridge between lesson-01 and lesson-02.

Now the important rule: **pointer arithmetic is scaled by the element size
automatically.** `arr + 1` does *not* add 1 byte — it adds *one whole element*
(= 4 bytes for `int`):

```
 arr          = 0x1000          (points at numbers[0])
 arr + 1      = 0x1004          ( +1 element  = +4 bytes )
 arr + 2      = 0x1008
 *(arr + 2)   = the value at 0x1008 = 30

 and by definition:
 arr[2]       ==  *(arr + 2)   ==  30      ← identical, always
```

So indexing is just **syntactic sugar** (a friendlier spelling) for *pointer
arithmetic + dereference*:

```
  arr[i]   is literally   *(arr + i)   is literally   *( base + i*size )
   \____________________________ same thing ___________________________/
```

This is *why* pointers had to come first: an array is a pointer in disguise.

### The dangerous part — no bounds checking

C does **NOT** check whether your index is inside the array. There is **no
bounds check** at runtime.

```c
int numbers[4];        // valid indexes: 0, 1, 2, 3
numbers[7] = 0xdead;   // index 7 is OUT OF BOUNDS — C does NOT stop you
```

What actually happens with `numbers[7]`:

```
 address = 0x1000 + (7 × 4) = 0x1000 + 28 = 0x101C
```

That address is **past the end of the array**. Whatever variable, saved
register, or return address happens to live at `0x101C` just got overwritten
with `0xdead`:

```
 THE ARRAY (4 slots)                    NEIGHBOURING MEMORY
 (what you "own")                       (NOT yours — but reachable)
 +------+------+------+------+   +------+------+------+------+
 | [0]  | [1]  | [2]  | [3]  |   | [4]  | [5]  | [6]  | [7]  | ...
 +------+------+------+------+   +------+------+------+------+
 0x1000                         0x1010              0x101C
                                 ^
                                 writing here corrupts whatever lives next:
                                 another variable? a saved pointer?
                                 the function's RETURN ADDRESS?
```

> **This is a buffer overflow.** The attacker's whole job in the next lessons is
> to (1) find an array (a "buffer") they can push too much into, and (2) arrange
> for the "neighbouring memory" they corrupt to be something powerful — most
> famously the **return address**, so the CPU jumps to code *they* chose.

You don't need to exploit it yet. You only need to **believe, at the byte level,
that writing past an array silently lands in the neighbour's memory.** That
belief is the foundation of everything from lesson-03 onward.

---

## 💡 Why does this matter in PWN?
Every classic memory-corruption bug — stack overflow, heap overflow,
out-of-bounds read/write — begins with an array (a *buffer*) being indexed or
filled past its real size. Because C computes `*(base + i*size)` blindly, an
out-of-range index is a perfectly valid machine operation that just happens to
touch memory you don't own. Master the array layout here and buffer overflow
stops being magic in the next phase — it becomes the obvious consequence of two
facts you already know: *elements are contiguous*, and *nobody checks the
bounds.*

---

## ✅ Check Your Understanding
Before moving on, answer for yourself (these are **not** graded — the graded
`QUIZ.md` is separate):

1. `char buf[8]` starts at address `0x4040`. What is the address of `buf[5]`?
2. `int arr[10]` starts at `0x600000`. What is the address of `arr[4]`?
   (element size = 4)
3. Rewrite `arr[6]` using the `*( ... )` pointer form.
4. In one sentence: *why* can C let you write to `data[99]` of an `int data[5]`
   array without any error?

If you can answer clearly, move to `TASKS.md`. If not, ask Claude to re-explain
in a different way — that's always welcome.
