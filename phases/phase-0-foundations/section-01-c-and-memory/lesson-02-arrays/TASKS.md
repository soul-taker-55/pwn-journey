# Lesson 02 Tasks: Arrays & Memory Layout

Tick each box when done, then commit.

## Practical tasks
- [ ] Read `LESSON.md` fully and answer the four "Check Your Understanding" questions for yourself.
- [ ] Compile and run the lab: `cd lab && gcc vuln.c -o vuln && ./vuln`
- [ ] Confirm from the output that each `int` address jumps by **4**, and each `char` address jumps by **1**.
- [ ] By hand (no running): for the `int numbers[4]` in the lab, predict `&numbers[3]` from `&numbers[0]`, then check it against the program's output.
- [ ] Prove `arr[i] == *(arr + i)`: edit `vuln.c` to also print `*(numbers + 2)` next to `numbers[2]`, recompile, and confirm they match.
- [ ] Open the program in GDB and watch the block in memory:
      `gdb ./vuln`, then `break main`, `run`, `next` a few times until the array is filled, then
      `print &numbers`, `print numbers`, and `x/4dw numbers` (examine 4 decimal words starting at the array).
- [ ] **Out-of-bounds, observed safely:** read the `OUT-OF-BOUNDS` section in `lab/README.md`, uncomment the one marked line in `vuln.c`, recompile with
      `gcc -fno-stack-protector vuln.c -o vuln_oob`, run it, and write one sentence about what changed in the neighbouring variable.

## External assignment
- [ ] Review the arrays/pointers relationship in one resource below, and log in `resources.md` what you learned.

## Resources (by priority)
1. **The C Programming Language (K&R) — Chapter 5, §5.3 "Pointers and Arrays"** — focus on: the array-name-is-a-pointer idea and `*(a+i) == a[i]` only. (Local copy: `resources/books/`.)
2. **CS:APP (Bryant & O'Hallaron) — §3.8 "Array Allocation and Access"** — focus on: how the compiler turns `arr[i]` into `base + i*size`. Overview: https://csapp.cs.cmu.edu/
3. **pwndbg cheat-sheet** — focus on: only `x/NFU` (examine memory) and `print` for now. https://github.com/pwndbg/pwndbg
4. **(Optional, visual)** "Arrays and pointers in C" — search YouTube — focus on: the contiguous-layout picture if you need reinforcement.

> Pass gate: tasks ticked + lab run + the out-of-bounds observation written down. Then do `QUIZ.md`.
