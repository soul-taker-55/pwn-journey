# My Notes — Lesson 01: Pointers (self-check review)

> My answers to the two "Check Your Understanding" questions, what was right, what was wrong, and the fuller explanation.

---

## Question 1 — What is the difference between `p`, `*p`, and `&x`?

### My answer
> `p` is a variable, the pointer itself, a box.
> `*p` is what the pointer `p` points to (which is `x`, or specifically the address of `x`).
> `&x` is the address of `x`.

### Verdict
| Part | Status | Note |
|------|--------|------|
| `p` is the pointer's own box | ✅ Correct | |
| `&x` is the address of `x` | ✅ Correct | |
| `*p` is `x` | ✅ Correct | `*p` and `x` are the same box |
| `*p` is "the address of `x`" | ❌ Wrong | The address of `x` is `&x`, and it is also what is stored in `p`. `*p` is the **value** inside `x`. |

The mix-up is between `p` and `*p`. They are one step apart:

- `p` → the address stored in the pointer
- `*p` → follow that address and get what is there

### Corrected answer
> `p` is a variable (a box) that stores an address. `&x` is the address of `x`. `*p` follows the address stored in `p` and gives the value there, which is `x` itself, not its address.

### Picture

```
   the note (p)              the house (x)
 ┌───────────────┐         ┌───────────────┐
 │ p lives at    │         │ x lives at    │
 │   0x2000      │         │   0x1000      │
 ├───────────────┤         ├───────────────┤
 │ contains:     │ ──────► │ contains:     │
 │   0x1000      │  leads  │   42          │
 └───────────────┘   to    └───────────────┘
```

| Expression | Means | Value here | Kind |
|-----------|-------|-----------|------|
| `x`  | the box named x | `42` | value |
| `&x` | address of x | `0x1000` | address |
| `p`  | content of p | `0x1000` | address |
| `*p` | thing at the address in p | `42` | value |
| `&p` | address of p itself | `0x2000` | address |

Reading rule: read `*` as **"the thing at"**, and `&` as **"the address of"**.

---

## Question 2 — If `p` points to `x`, what does `*p = *p + 1;` do to `x`?

### My answer
> It makes `p` point to the address that comes after `x`.

### Verdict
❌ Wrong. The line changes the **value of `x`**, and `p` does not move.

What I described is a different line: `p = p + 1;`.

### Corrected answer
> `*p = *p + 1;` reads the value at the address in `p` (42), adds 1, and writes 43 back into the same box. So `x` becomes 43. `p` still points to `x`.

### Why: trace it

`*p` is the same box as `x`, so the line is the same as `x = x + 1;`.

```
BEFORE:   x = 42        p = 0x1000

step 1 (right side, *p + 1):
          follow p to 0x1000, READ 42, add 1  → 43

step 2 (left side, *p = ...):
          follow p to 0x1000, WRITE 43 into that box

AFTER:    x = 43        p = 0x1000   (p did not change)
```

### The line I was actually describing

```c
p = p + 1;      /* no * anywhere: this changes the pointer, not x */
```

```
BEFORE:   x = 42        p = 0x1000
AFTER:    x = 42        p = 0x1004
```

- `x` is untouched.
- `p` moved 4 bytes because an `int` is 4 bytes. A pointer to `int` moves in steps of `int`. (Full details in lesson 02, arrays and address arithmetic.)
- If I now wrote `*p`, I would read whatever sits at `0x1004`. That is not `x`. This is the seed of an out-of-bounds read, a core PWN bug class.

My instinct of "p moves to what comes after x" was a valid idea. It was attached to the wrong line.

### Side by side

| Line | What it changes | `x` after | `p` after |
|------|-----------------|-----------|-----------|
| `*p = *p + 1;` | the box **p points to** | 43 | `0x1000` (same) |
| `p = p + 1;`   | **p itself** | 42 (same) | `0x1004` |

**Rule:** a `*` on the left of `=` means "write into the box at that address". No `*` means I am changing the pointer variable itself.

---

## More explanation

### 1. The `*` symbol has two jobs
This is the most common source of confusion.

```c
int *p = &x;    /* here * is part of the TYPE: "p is a pointer to int" */
*p = 99;        /* here * is an OPERATION: "go to the address in p"    */
```

- In a **declaration**, `*` says what kind of variable this is.
- In an **expression**, `*` means follow the pointer.

### 2. `&` and `*` undo each other
- `&x` gives the address of `x`.
- `*` of an address gives the thing there.
- So `*&x` is just `x`.
- And `&*p` is just `p`.

### 3. A pointer is also a variable with its own address
`p` is a box, so it has an address too: `&p`. Pointer-to-pointer (`int **pp = &p;`) comes later, and it is exactly this idea applied once more.

### 4. The type matters
`int *p` means "the thing at this address is an `int`". That is why `*p` reads 4 bytes and why `p + 1` steps 4 bytes. A pointer is not just a number; the type tells the compiler how much to read and how far to step.

### 5. Why PWN cares
- `*p = value` is a **write primitive**: if an attacker controls `p`, they choose where memory is written.
- `*p` is a **read primitive**: if an attacker controls `p`, they choose what memory is read.
- Most memory-corruption bugs end up giving the attacker control of some pointer or some address.

---

## Verify it myself (run in the lab)

```c
#include <stdio.h>

int main(void) {
    int x = 10;
    int *p = &x;

    printf("x   = %d\n", x);
    printf("&x  = %p\n", (void *)&x);
    printf("p   = %p\n", (void *)p);
    printf("*p  = %d\n", *p);
    printf("&p  = %p\n", (void *)&p);

    *p = *p + 1;
    printf("\nafter *p = *p + 1 : x = %d, p = %p\n", x, (void *)p);

    p = p + 1;
    printf("after p = p + 1   : x = %d, p = %p\n", x, (void *)p);
    /* do NOT print *p here: it is not x anymore */
    return 0;
}
```

What to confirm in the output:
- `&x` and `p` show the **same** address.
- `&p` shows a **different** address.
- After `*p = *p + 1`: `x` is 11 and `p` is unchanged.
- After `p = p + 1`: `x` is still 11 and `p` grew by `0x4`.

---

## Re-check (answer in my own words)

```c
int x = 10;
int *p = &x;
*p = *p * 2;
p = p + 1;
```

1. After the first two lines, which of `x`, `p`, `*p`, `&x` are addresses and which are values?
   - My answer:
2. After `*p = *p * 2;` what is `x`? Did `p` change?
   - My answer:
3. After `p = p + 1;` does `p` still point to `x`? Is `x` still the same value as in question 2?
   - My answer:

## One-line summary
`p` = the address in the pointer · `*p` = the value at that address · `&x` = the address of x · `*` on the left of `=` writes into the target, no `*` changes the pointer.
