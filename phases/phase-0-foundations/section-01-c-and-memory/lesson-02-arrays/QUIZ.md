# Lesson 02 Quiz: Arrays & Memory Layout

Answer in `ANSWERS.md`, then commit. Do not look at any solution before trying.
Show your arithmetic where a calculation is asked.

1. In your own words: what does it mean that an array is stored **contiguously**,
   and what single fact about the element type decides the gap between
   consecutive element addresses?

2. `int arr[6]` starts at base address `0x5000` (element size = 4 bytes).
   Compute the addresses of `arr[0]`, `arr[3]`, and `arr[5]`.

3. The array name `numbers` and the expression `&numbers[0]` always hold the
   same value. Why? (One or two sentences.)

4. Rewrite each of these using the **other** form (indexing ↔ pointer):
   - `arr[4]`  →  `*( ___ )`
   - `*(buf + 2)`  →  `buf[ ___ ]`

5. **Applied / the PWN hook:** `char buf[8]` is a buffer with valid indexes 0..7.
   An attacker controls the index `i` in `buf[i] = 0x41;`.
   (a) Which is the **smallest** value of `i` that writes **outside** the buffer?
   (b) In one sentence, explain why the C program will happily perform that write
   with no error — tie it to the `*(base + i*size)` formula.

> Pass mark: 4 of 5.
