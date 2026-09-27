# Lab — Lesson 01: Pointers

## Goal
See with your own eyes that a pointer stores an address, and that modifying through it changes the original variable.

## Run
```bash
gcc vuln.c -o vuln
./vuln
```

## Your task
1. Run the program and observe the output.
2. Open it in GDB and watch the address and value:
   ```bash
   gdb ./vuln
   (gdb) break main
   (gdb) run
   (gdb) print &x
   (gdb) print x
   (gdb) print p
   ```
3. Modify `vuln.c` as in TASKS.md, then recompile and run.

> Note: this lab is "white box" (with source) for understanding. In later phases we'll strip the source and attack the binary directly as a black box.
