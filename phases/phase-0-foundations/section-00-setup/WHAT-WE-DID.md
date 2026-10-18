# What We Did — Section 00 Setup (plain explanation)

A step-by-step record of the environment setup, with **why** each piece exists.
Completed 2026-10-18 on Ubuntu 24.04.5 LTS.

---

## The goal
Build the toolkit used for the whole PWN journey: a way to **compile** C programs,
**inspect** them while they run, and **write exploit scripts** against them.

```
   C source  ──gcc──▶  binary  ──gdb+pwndbg──▶  watch it run
                                   │
                              pwntools ──▶ exploit.py talks to the binary
```

---

## Step 0 — `lsb_release -a`  (confirm the OS)
Prints the Linux distribution name and version. We confirmed **Ubuntu 24.04.5 LTS**.
Why: the rest of the steps assume Debian/Ubuntu package names (`apt`).

## Step 1 — `sudo apt update && sudo apt upgrade -y`  (refresh the system)
- `apt update` = refresh the **index** (the catalog of available packages + versions).
- `apt upgrade` = install the newest versions of what's already installed.
Why: start from a known, current base so later installs resolve cleanly.

## Step 2 — Core build + debug tools
`build-essential gdb git python3 python3-pip python3-venv checksec`
- **gcc** (inside build-essential): the C **compiler** — turns `.c` source into an
  executable the CPU runs.
- **gdb**: the **debugger** — runs a program and lets us pause it, read CPU registers,
  and inspect memory while it executes. This is the core PWN microscope.
- **git**: version control (this repo).
- **python3 / pip / venv**: Python + its package installer + isolated-environment tool.
- **checksec**: prints which **security protections** a binary was built with
  (canary, NX, PIE, RELRO…). We read these before attacking any binary.

## Step 3 — pwndbg  (makes GDB readable)
Plain GDB is terse. **pwndbg** is a GDB extension that, on every stop, shows a clear
dashboard: registers, disassembly, the stack, and a backtrace, all colour-coded.
Installed by cloning the repo and running `./setup.sh`, which also added
`source ~/pwndbg/gdbinit.py` to `~/.gdbinit` so it loads automatically every time GDB starts.

Note: the first `./setup.sh` failed once with `Could not resolve host: github.com`
(a transient DNS/connection hiccup). Re-running it resumed from cache and succeeded —
a good habit: **re-run, don't restart from zero** when a download drops mid-way.

## Step 4 — pwntools  (exploit-writing library) in a venv
**pwntools** is a Python library that makes exploit scripts short: start a process,
send/receive bytes, pack numbers into the exact byte layout memory expects, etc.
Installed inside a **venv** (virtual environment) — an isolated Python world whose
packages don't clash with the system's.

Path note: this install lives at **`~/pwn-venv`** (not the `~/pwn/.venv` the SETUP.md
example shows). An alias `pwn` was added to `~/.bashrc`:
```bash
alias pwn="source ~/pwn-venv/bin/activate"
```
So each new terminal: type `pwn` → the prompt shows `(pwn-venv)` → pwntools is available.
Verified: `python3 -c "import pwnlib; print(pwnlib.__version__)"` → `4.15.0`.

## Step 5 — First habit: compile a program and watch it in GDB
We wrote `test.c` — a tiny program that demonstrates a **pointer** (a variable that
holds the memory address of another variable), then **writes through** that pointer to
change the original value from 42 to 99. This is a direct preview of lesson-01 (Pointers).

Compiled deliberately **without modern protections** to keep early labs simple:
```bash
gcc -g -fno-stack-protector -no-pie -z execstack test.c -o test
```
- `-g` = include debug symbols (so GDB shows source lines and variable names).
- `-fno-stack-protector` = disable the **stack canary** (a guard value that detects
  stack overflow). Off = overflows are easier to study.
- `-no-pie` = fixed load address (not randomized), so addresses are predictable.
- `-z execstack` = mark the stack **executable** (lets shellcode on the stack run later).

`checksec` on the result confirmed: **No canary, No PIE, Executable stack** — exactly
the "training wheels off" target we want for the first labs.

In GDB (`break main` → `run` → `info registers`) we paused at the start of `main` and
saw the live CPU registers and the stack — the everyday loop of binary exploitation.

---

## End state (what you have now)
- Ubuntu 24.04 with gcc, gdb (+ pwndbg auto-loaded), git, python3, checksec.
- pwntools 4.15.0 in `~/pwn-venv` — run `pwn` to activate it each session.
- A working compile → run → debug loop, proven on `test.c`.

**Next:** Phase 0 / Section 01 → `lesson-01-pointers`.
