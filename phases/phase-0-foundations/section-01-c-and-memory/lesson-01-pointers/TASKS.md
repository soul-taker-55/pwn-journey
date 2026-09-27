# Lesson 01 Tasks: Pointers

Tick each box when done, then commit.

## Practical tasks
- [ ] Read `LESSON.md` fully and answer the two "Check Your Understanding" questions for yourself.
- [ ] Compile and run the lab: `cd lab && gcc vuln.c -o vuln && ./vuln`
- [ ] Modify `vuln.c`: add a second pointer to the same variable and print the value through it.
- [ ] Open the program in GDB and watch the variable's address and value: `gdb ./vuln`, then `break main`, `run`, `print &x`, `print x`.
- [ ] Write your own small program: a pointer that changes a variable's value, and confirm the change appears.

## External assignment
- [ ] Review the pointers chapter in one resource below, and log in `resources.md` what you learned.

## Resources (by priority)
1. **The C Programming Language (K&R) — Chapter 5** — focus on: pointers and their relation to arrays only, not the whole chapter.
2. **[Pointers explained — search YouTube]** — focus on: the visual idea (address vs value) if you need reinforcement.
3. **[GDB pwndbg — cheat sheet](https://github.com/pwndbg/pwndbg)** — focus on: only `print`, `x`, and `break` for now.
