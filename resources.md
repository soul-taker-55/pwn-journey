# 📚 Resources — PWN Journey

External materials that feed the journey, ordered by priority per topic.
Each entry has a **Focus on** line (what to extract) and a **What I learned** field
(fill it after you study it — proof of absorption, not just a saved link).

**The three pillars (fully free, make you independent of AI):**
1. **pwn.college** — the spine: lectures + graded challenges → https://pwn.college
2. **Nightmare** — written walkthroughs mapping concepts to real CTF binaries → https://guyinatuxedo.github.io
3. **ROP Emporium** (ROP) + **how2heap** (heap) — targeted practice for the two hardest phases.

> Pattern each module: pwn.college lecture → INE course (depth) → book chapter (anchor) → pwn.college challenges → write it up in the repo.

---

## Phase 0 — C & Memory  *(neither pwn.college nor INE teach this — it's on us)*

1. **The C Programming Language** — K&R
   - Focus on: pointers, arrays, structs, manual memory (`malloc`/`free`).
   - What I learned: _____
2. **Computer Systems: A Programmer's Perspective (CS:APP)** — ch. 1–3 → https://csapp.cs.cmu.edu
   - Focus on: how C maps to memory and machine code; the stack.
   - What I learned: _____
3. **Beej's Guide to C** (free) → https://beej.us/guide/bgc/
   - Focus on: quick, practical pointer/memory refresher.
   - What I learned: _____

## Phase 1 — Assembly & Debugging

| Priority | Resource | Focus on |
|---|---|---|
| pwn.college | Assembly Crash Course · Debugging Refresher → https://pwn.college | reading/writing x86-64; stepping in a debugger |
| INE | System Security & x86 Assembly Fundamentals · x86/x86_64 Assembly & Shellcoding on Linux · GDB Megaprimer | registers, calling convention, GDB fluency |
| Book | CS:APP ch.3 · *Programming from the Ground Up* (Bartlett, free) → https://savannah.nongnu.org/projects/pgubook/ | assembly from first principles |
| Free | OpenSecurityTraining2 — Arch1001 x86-64 Asm → https://ost2.fyi | deep, structured asm |
| Tool | pwndbg → https://github.com/pwndbg/pwndbg | the debugger you'll live in |

- What I learned (Phase 1): _____

## Phase 2 — Stack Overflow & Shellcode

| Priority | Resource | Focus on |
|---|---|---|
| pwn.college | Memory Errors · Shellcode Injection → https://pwn.college | overwriting the return address; running your own code |
| INE | Exploit Development: Buffer Overflows · Python for Pentesters (pwntools) | the classic overflow; scripting exploits |
| Book | **Hacking: The Art of Exploitation** — Erickson | the single best intro to exploitation |
| Paper | Phrack #49 — *Smashing the Stack for Fun and Profit* (free) → http://phrack.org/issues/49/14.html | the origin text of stack smashing |
| Tool | pwntools docs → https://docs.pwntools.com | `p64`, `recvuntil`, `process` |

- What I learned (Phase 2): _____

## Phase 3 — Bypassing Mitigations (NX · ASLR · Canary · Format String)

| Priority | Resource | Focus on |
|---|---|---|
| pwn.college | Sandboxing · Return Oriented Programming · Format String Exploits → https://pwn.college | ROP chains; `%n` writes; defeating a leak |
| INE | Linux Exploit Development | ret2libc, ROP, leaks end-to-end |
| Practice | **ROP Emporium** (free, gold standard) → https://ropemporium.com | building ROP chains, step by step |
| Free | Nightmare — fmt-string & ROP sections → https://guyinatuxedo.github.io | worked CTF examples |
| Paper | Phrack #59 — *Format String Exploits* (free) → http://phrack.org/issues/59/7.html | the mechanism in depth |

- What I learned (Phase 3): _____

## Phase 4 — Heap Exploitation

| Priority | Resource | Focus on |
|---|---|---|
| pwn.college | Dynamic Allocator Misuse → https://pwn.college | UAF, double-free, tcache |
| INE | Linux Exploit Development (advanced sections) | applying heap primitives |
| Practice | **how2heap** (shellphish, free, canonical) → https://github.com/shellphish/how2heap | every heap technique, per glibc version |
| Free | Azeria heap series → https://azeria-labs.com | clear diagrams of glibc malloc |

- What I learned (Phase 4): _____

## Phase 5 — Reverse Engineering, Race/Kernel & Specialization

| Priority | Resource | Focus on |
|---|---|---|
| pwn.college | Binary Reverse Engineering · Race Conditions · Kernel → https://pwn.college | reading stripped binaries; TOCTOU; kernel intro |
| INE | Reverse Engineering Foundations → Practical RE → RE Linux 32-bit · Embedded/IoT Linux for Red-Blue Teams · Malware Analysis | Ghidra/IDA workflow; black-box; IoT |
| Book | *Practical Reverse Engineering* (Dang) · **The Ghidra Book** · *Practical Malware Analysis* | the RE toolkit |
| Book | *The IoT Hacker's Handbook* · *Practical IoT Hacking* | firmware/embedded direction |

- What I learned (Phase 5): _____

---

## Certification note
- **eCXD / eCRE (INE):** exam retired — use the INE **training** only, not as a cert goal.
- **Cert endpoint:** **OSED** (Offensive Security, EXP-301) — the live, recognized binary-exploitation cert.
- **Real proof of skill:** this public repo (labs + write-ups) + CTF solves (pwn.college belts, picoCTF, pwnable.kr/tw, HTB pwn).

---

## All-phases free safety net
- **pwn.college** — https://pwn.college (spine + labs + belts)
- **Nightmare / guyinatuxedo** — https://guyinatuxedo.github.io (written walkthroughs)
- **LiveOverflow — Binary Exploitation** — https://www.youtube.com/playlist?list=PLhixgUqwRTjxglIswKp9mpkfPNfHkzyeN
- **CTFs:** picoCTF · pwnable.kr · pwnable.tw · HTB (pwn category)