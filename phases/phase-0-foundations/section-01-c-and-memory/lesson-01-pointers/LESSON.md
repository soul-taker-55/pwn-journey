# Lesson 01: Pointers

> **Phase:** 0 · **Section:** 01 · **Estimated time:** 2–3 hours

## 🎯 Lesson Goal
Understand what a **pointer** really is at the memory level — not as a textbook definition, but so you can picture exactly what happens in memory on each line. This concept is the foundation of the entire field that follows.

## 🧩 Prerequisite
Basic C (variables, functions, printing with `printf`). Nothing more.

---

## 📖 Explanation

### Memory is a street of numbered boxes
Picture the computer's memory (RAM) as a long street of boxes. Each box has a unique number called its **address**, and holds a **value** inside.

When you write `int x = 42;`, the computer reserves a box, stores `42` in it, and names it `x`. But this box also has a numeric address (e.g. `0x7ffe1234`).

### A pointer = a box that stores another box's address
A **pointer** is an ordinary variable, but instead of storing a value like `42`, it stores the **address** of another variable. In other words, it "points" to a location in memory.

```c
int x = 42;        // an ordinary variable, value 42
int *p = &x;       // a pointer p storing the address of x
```

- `&x` means: "the **address** of x" (the `&` symbol = take the address).
- `int *p` means: "p is a pointer to an integer (int)".
- `*p` means: "the **value stored at the address p points to**" (this operation is called *dereferencing*).

### 🖼️ Diagram

```
      variable x                    pointer p
   ┌─────────────┐              ┌──────────────┐
   │ address:    │              │ address:     │
   │ 0x7ffe1234  │              │ 0x7ffe5678   │
   ├─────────────┤              ├──────────────┤
   │ value: 42   │◄─────────────┤ 0x7ffe1234   │
   └─────────────┘   points to  └──────────────┘

   x    == 42            (the value itself)
   &x   == 0x7ffe1234    (address of x)
   p    == 0x7ffe1234    (p stores the address of x)
   *p   == 42            (go to the address in p, find 42)
```

The key point: `p` and `x` are two different boxes with two different addresses. But the **content** of `p` is the **address** of `x`. So when you dereference with `*p`, you reach `x` itself.

### Modifying through a pointer
Since `*p` actually reaches `x`, writing through it changes `x`:

```c
*p = 99;    // this changes x itself to 99!
printf("%d", x);   // prints 99
```

This ability — modifying a variable through its address rather than its name — is exactly what an attacker exploits later.

---

## 💡 Why does this matter in PWN?
The entire PWN field is built on **manipulating memory through its addresses**. Every vulnerability we'll learn later — from Buffer Overflow to Use-After-Free — comes down to: making a program read or write an address it was never supposed to touch. Anyone who doesn't deeply understand pointers cannot understand any vulnerability after them. This lesson isn't a passing "intro to C" — it's the lens through which you'll see the whole field.

## ✅ Check Your Understanding
Before moving on, answer for yourself:
1. What is the difference between `p`, `*p`, and `&x`?
2. If `p` points to `x`, what does the line `*p = *p + 1;` do to the value of `x`?

If you can answer clearly, move to `TASKS.md`. If not, ask Claude to re-explain in a different way — that's always welcome.
