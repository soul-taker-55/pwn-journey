# Lab — Lesson 02: Arrays & Memory Layout

## Goal
See with your own eyes that:
1. an array is a **contiguous block** — addresses step by exactly the element size,
2. the array name **is** the address of element 0,
3. `arr[i]` and `*(arr + i)` give the **same** value, and
4. writing **past the end** of an array silently lands in neighbouring memory
   (a one-element buffer overflow).

## Run (normal)
```bash
gcc vuln.c -o vuln
./vuln
```

What to confirm in the output:
- `numbers[i]` addresses increase by **4** each step (int = 4 bytes).
- `name[i]` addresses increase by **1** each step (char = 1 byte).
- `numbers` and `&numbers[0]` print the **same** address.
- `numbers[2]` and `*(numbers + 2)` print the **same** value.

## Watch it in GDB
```bash
gdb ./vuln
(gdb) break main
(gdb) run
(gdb) next          # repeat until the arrays are initialised
(gdb) print &numbers
(gdb) print numbers
(gdb) x/4dw numbers # 4 decimal words from the array start -> 10 20 30 40
(gdb) x/4xb name    # 4 hex bytes of the char array -> 50 57 4e 00  (P W N \0)
```
`x/NFU addr` = examine **N** units, format **F** (d=decimal, x=hex), size **U**
(b=byte, w=4-byte word). So `x/4dw` = 4 decimal words.

## OUT-OF-BOUNDS (the point of the whole lesson)
1. In `vuln.c`, find the line marked `uncomment ME` and remove the leading `//`:
   ```c
   numbers[4] = 0xdead;
   ```
   `numbers` only has valid indexes 0..3, so `numbers[4]` is one element past
   the end. C does **not** stop you.
2. Compile **without** the stack protector so the layout is simple and the
   neighbour is reachable:
   ```bash
   gcc -fno-stack-protector vuln.c -o vuln_oob
   ./vuln_oob
   ```
   > `-fno-stack-protector` turns off a compiler defence that would otherwise
   > detect this and abort. We disable it here only to make the raw behaviour
   > visible; we'll study that defence properly in Phase 3.
3. Compare `canary ... before` and `canary ... after`. If `after` shows `0xdead`
   (or anything other than `0x1111`) even though you never wrote to `canary` by
   name, you just watched an out-of-bounds array write corrupt its neighbour.

> Layout is not guaranteed: the compiler may reorder locals or add padding, so
> `numbers[4]` might hit `canary`, some padding, or another slot. If `canary`
> doesn't change, try `numbers[5]`/`numbers[6]`, or inspect the real layout in
> GDB with `print &numbers[0]` and `print &canary` and compute which index lands
> on the canary. The lesson is the *principle*, not one magic index.

> Note: this lab is "white box" (you have the source) for understanding. In
> later phases we'll strip the source and attack the binary directly as a black
> box.
