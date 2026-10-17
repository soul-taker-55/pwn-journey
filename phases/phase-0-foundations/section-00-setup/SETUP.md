# Phase 0 — Environment Setup (Ubuntu)

Goal: a working Ubuntu box with GDB + pwndbg, pwntools, gcc, and python3 — the
toolkit you live in for the whole journey. Run each block, then run its **Verify**
line. Do not move on until Verify succeeds.

## 0. Confirm you're on Ubuntu
```bash
lsb_release -a
```
Verify: shows Ubuntu (22.04 / 24.04 or similar).

## 1. Update the system
```bash
sudo apt update && sudo apt upgrade -y
```

## 2. Core build + debug tools
```bash
sudo apt install -y build-essential gdb git python3 python3-pip python3-venv checksec
```
Verify:
```bash
gcc --version && gdb --version && python3 --version
```
(build-essential = gcc/make; checksec shows a binary's protections.)

## 3. pwndbg — makes GDB readable
```bash
cd ~
git clone https://github.com/pwndbg/pwndbg
cd pwndbg
./setup.sh
```
Verify: run `gdb` — you should land on a `pwndbg>` prompt. Type `quit` to exit.

## 4. pwntools — in a dedicated venv (clean & reproducible)
```bash
mkdir -p ~/pwn && cd ~/pwn
python3 -m venv .venv
source .venv/bin/activate
pip install --upgrade pip
pip install pwntools
```
Verify:
```bash
python3 -c "from pwn import *; print(pack(0x41))"
```
Expect: `b'A\x00\x00\x00\x00\x00\x00\x00'`.
Each new session: `source ~/pwn/.venv/bin/activate` before running exploit scripts.
Quick alternative (no venv): `pip install --break-system-packages pwntools`.

## 5. First habit — compile and watch memory in GDB
Create `test.c`:
```c
#include <stdio.h>
int main(void) {
    int x = 42;
    int *p = &x;
    printf("x = %d, stored at %p\n", x, (void*)p);
    *p = 99;                 // write through the pointer
    printf("now x = %d\n", x);
    return 0;
}
```
Compile WITHOUT modern protections (keeps the early labs simple):
```bash
gcc -g -fno-stack-protector -no-pie -z execstack test.c -o test
```
Verify:
```bash
./test
checksec --file=./test      # expect: No canary, NX disabled, No PIE
gdb ./test                  # then:  break main -> run -> info registers -> quit
```
Done when: `./test` prints x going 42 -> 99, and you stepped through it in GDB.

---
Next: Phase 0 / Section 01 — C and Memory (lesson-01-pointers).
