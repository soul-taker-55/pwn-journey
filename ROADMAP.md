# 🎯 PWN Roadmap — Binary Exploitation

A practical, structured path into Binary Exploitation. Work the items in order and check off every step you complete. Each phase ends with a **Resources** section that tells you exactly what to focus on in each course, book, or video series.

---

## ℹ️ Before You Start — General Info

Read this section once before diving into the phases.

### What is PWN, in short?
**PWN** (Binary Exploitation) is the art of exploiting how programs handle memory, turning a simple bug into full control of the program's execution — usually ending in a **shell** on the target system. You're not attacking a website or a network here; you're attacking **the binary itself**: studying how it arranges data in memory, and exploiting the moment it writes outside the allowed space. It's the deepest offensive layer in cybersecurity, and the closest to the machine's core.

### The most important idea: you usually have no source code (the black box)
This is the single most important fact in the field, and the source of all its value: in real work you **rarely have the source code** of the program you're attacking. If source were always available, companies would just use a code auditor. A PWN engineer's value shows up precisely when there's only a closed binary — a router you bought, a camera's firmware, a commercial program.

Your weapon then is **Reverse Engineering**: you take the binary (zeros and ones) and turn it back into readable form using tools like **Ghidra** or **IDA** — into Assembly, or a distorted approximation of C. This is exactly why we set Assembly as your real gap: without it you're blind in front of any closed file. Your path with a black box: reverse-engineer to understand → find a memory weakness → build the exploit → take control, without seeing a single line of the original.

- ⬛ **Black box (no source)** — the most common and highest-value. All IoT/OT devices are here.
- 🔲 **Gray box** — partial source.
- ⬜ **White box** — full source. Rare in this field.

> **A common trap:** learning platforms give you the source with the challenge to simplify the start — pedagogically fine. But move to "no source" challenges early (pwnable.tw, HTB Pwn), or you'll get dependent on a crutch you won't have in real work.

### Career scenarios — where is this skill applied?
A PWN engineer isn't hired to exploit programs all day. The skill itself is a base language that opens five different roles:
1. **Vulnerability Researcher:** finds undiscovered (zero-day) vulnerabilities in a program or device before attackers. Highest-paid and rarest; needs Phase 4–5.
2. **Hardware/Product Pentester (closest fit for a web pentester):** move from testing a website to testing a real device (router, camera, industrial sensor). Companies are legally obliged to test their devices, and few can open and exploit firmware. This is where the skill meets OT/IoT security.
3. **Exploit/Tooling Developer:** inside a Red Team, you write the custom tools that AV doesn't detect. The weapon engineer, not the field operator.
4. **Malware Analyst:** the same PWN muscle in reverse — you take apart malware to understand and stop it. A senior Blue Team role needed in every mature SOC.
5. **Device Security Trainer/Expert:** you stand in front of a client and hack a real device in front of them — turning training from "explanation" to "proof".

### Core tips
1. This field pays off late. You won't earn much in the first 6 months, and you may get frustrated — that's normal. Those who persist join a small, hard-to-replace group.
2. Try the challenge yourself first (at least an hour); only watch the solution if you're stuck. Watching before trying doesn't teach in this field.
3. Live inside GDB. Watch memory visually — don't just read or imagine the code.
4. Write a write-up for every challenge you solve. Published proof of work gets you hired more than any certificate.

### Tools you'll live with
- **GDB + pwndbg** — the debugger you'll watch memory with, line by line.
- **pwntools** — a Python library for building and automating exploits (your Python background helps here).
- **Ghidra / IDA** — reverse engineering: disassembling and reading closed files.
- **binwalk** — extracting firmware from IoT/OT devices.
- **checksec / ropper** — checking a binary's protections and finding gadgets.

---

## Phase 0 — Foundations (Environment + C/Assembly)
**Duration: 4–6 weeks · The real starting point**
**Goal:** read Assembly code and understand what it does to memory. This is your real gap — you already have everything else.

### Environment setup
- [ ] Install a Linux system for work — Ubuntu is perfectly enough (no need for Kali here). A VM (VMware/VirtualBox) works.
- [ ] Install the **GDB** debugger with the **pwndbg** extension — [github.com/pwndbg/pwndbg](https://github.com/pwndbg/pwndbg)
- [ ] Install **pwntools** via Python: `pip install pwntools`
- [ ] Install the `gcc` compiler and confirm `python3` works.

### Revive C — focused on memory only
- [ ] Master **pointers** and pointers-to-pointers (a pointer stores an address, not a value).
- [ ] Understand how **arrays** are stored contiguously in memory (this is where overflow happens).
- [ ] Distinguish the **Stack** (auto-managed) from the **Heap** (manually allocated).
- [ ] Master manual allocation: `malloc` and `free`.

### First correct habit
- [ ] 🏁 Write a small C program, open it in GDB, and watch variables in memory step by step. This habit — watching inside GDB — is the core of the whole specialization.

### 📚 Resources
- **[OverTheWire — Bandit](https://overthewire.org/wargames/bandit/)** (platform, free) — focus on: mastering the Linux command line until it's automatic. Don't skip this; friction with Linux later costs you hours.
- **The C Programming Language — K&R** (book, most important) — focus on: chapters 5 and 6 only (pointers and structs). The only goal: understand what happens in memory on each line, not to become a pro C programmer.
- **Pointers explained (search: "pointers in C") + "GDB tutorial for beginners"** (video) — focus on: if a concept is hard, start with a short visual explanation of pointers, then return to the primary source.

---

## Phase 1 — Assembly & Computer Architecture
**Duration: 3–4 weeks · Platform: PWN.College**
**Goal:** read Assembly and understand registers, the stack, and how functions are called and return.

### Assembly Crash Course
- [ ] Create an account on **[PWN.College](https://pwn.college/)** and start the Assembly Crash Course.
- [ ] Understand the **registers** (rax, rbx, rsp, rip) and each one's role.
- [ ] Master the core instructions: `push` · `pop` · `mov` · `call` · `ret`.
- [ ] Understand how the stack physically works when a function is called and returns.

### Computer architecture (your engineering background helps — you'll move fast)
- [ ] Complete the Computer Architecture track on PWN.College.

### Transition milestone
- [ ] 🏁 Open a simple function in GDB and explain in your own words what happens on the stack when it's called and when it returns.

### 📚 Resources
- **[PWN.College — Computer Architecture & Assembly Crash Course](https://pwn.college/)** (platform, the backbone) — this is your primary platform throughout (ASU, free, video + challenges). Watch the video, then solve its challenges immediately — don't watch without solving.
- **[Azeria Labs — Assembly Basics](https://azeria-labs.com/writing-arm-assembly-part-1/)** (reference, free) — focus on: a clear written reference for Assembly and registers if you need text alongside PWN.College's videos.
- **[OpenSecurityTraining2 — Architecture 1001 (x86-64 Assembly)](https://ost2.fyi/Arch1001.html)** (video series) — optional, only if PWN.College's base feels insufficient. Focus on: the calling convention and stack layout.

---

## Phase 2 — Classic Stack Exploitation (your first real hack)
**Duration: 4–5 weeks · Here you feel your first "control"**
**Goal:** take control of a real program's execution — the first hack, the one that anchors you psychologically.

### Program Interaction
- [ ] PWN.College Program Interaction track: sending crafted input to a program (first real use of pwntools).

### Stack Buffer Overflow
- [ ] Understand **Stack Buffer Overflow** in theory (overfilling a buffer overwrites the return address — the classic gateway).
- [ ] Execute your first overflow: overwrite the return address and redirect the program (PWN.College Memory Errors).
- [ ] Learn **Shellcode Injection**: injecting machine code to open a shell ("getting a shell").

### First documented achievement
- [ ] 🏁 Solve your first real PWN challenge and write a short write-up. Try the easy category on [pwnable.tw](https://pwnable.tw) and [pwnable.kr](http://pwnable.kr).

### 📚 Resources
- **[CryptoCat — Intro to Binary Exploitation](https://www.youtube.com/playlist?list=PLHUKi1UlEgOIc07Rfk2Jgb5fZbxDPec94)** (video series, best for beginners) — focus on: Buffer Overflow step by step with the tools (GDB, pwntools, Ghidra, checksec). Match each video with a challenge you solve by hand right after.
- **[PWN.College — Program Interaction & Memory Errors](https://pwn.college/)** (platform, same path) — focus on: Program Interaction (pwntools in practice) and Memory Errors (first stack overflow).
- **[Nightmare (GuyInATuxedo)](https://guyinatuxedo.github.io/)** (challenges) — focus on: after learning a technique on PWN.College, find its section in Nightmare and solve its challenges to cement it.
- **[picoCTF — Binary Exploitation](https://play.picoctf.org/)** (challenges, beginner) — focus on: gentle challenges before pwnable.tw. Start easy, write a write-up for each.

---

## Phase 3 — Bypassing Modern Mitigations
**Duration: 6–8 weeks · The real specialization begins here**
**Goal:** deal with real, defended programs — bypassing protections is the core of professional skill.

### ROP and bypassing execution prevention
- [ ] Master **ROP** (Return-Oriented Programming) — reusing existing code chunks (gadgets) to bypass NX/DEP.
- [ ] Understand **NX / DEP** and how ROP works around it.

### Remaining protections
- [ ] Bypass **ASLR** (address space layout randomization) — learn to leak an address to defeat it.
- [ ] Bypass **Stack Canaries** (a secret value guarding the return address).
- [ ] Master **Format String** vulnerabilities (read/write memory via printf misuse).

### Real friction
- [ ] 🏁 Compete in live **CTFs** — PWN category only — via [ctftime.org](https://ctftime.org). Live competition accelerates learning enormously.

### 📚 Resources
- **[ROP Emporium](https://ropemporium.com/)** (focused training, indispensable) — 8 challenges built to teach ROP alone, in order (ret2win → split → callme → write4 → badchars → fluff → pivot → ret2csu). Solve them in order on x86_64; don't move on until you understand the previous one.
- **[CryptoCat — ROP Emporium Series](https://www.youtube.com/c/cryptocat23)** (video, companion) — focus on: try the challenge yourself first for an hour; if stuck, watch. Don't watch before trying.
- **[PWN.College — Return-Oriented Programming](https://pwn.college/)** (platform, same path) — focus on: the ROP and mitigations (ASLR, Canary, Format String) tracks. Study in parallel with ROP Emporium.
- **[Ir0nstone — Binary Exploitation Notes](https://ir0nstone.gitbook.io/notes)** (written reference, excellent) — focus on: a dictionary you return to for each new technique — the Stack and ASLR-bypass sections.

---

## Phase 4 — Heap Exploitation (what separates pro from amateur)
**Duration: 8–12 weeks · The deepest part of the field**
**Goal:** master the hardest layer — exploiting dynamic memory allocators.

### Heap fundamentals
- [ ] Understand how the **glibc malloc** allocator works internally (required for any heap exploit).

### Heap exploitation techniques
- [ ] Master **Use-After-Free (UAF)** — using a pointer after its memory is freed.
- [ ] Master **Double Free** and Tcache / Fastbin attacks.

### References & practice
- [ ] Study the PWN.College heap track + the **[how2heap](https://github.com/shellphish/how2heap)** series (Shellphish — the world's most famous practical heap guide, free on GitHub).
- [ ] 🏁 Solve intermediate heap challenges on pwnable.tw.

### 📚 Resources
- **[how2heap — Shellphish](https://github.com/shellphish/how2heap)** (reference, the global standard) — focus on: run each example yourself inside GDB and watch what happens in memory — don't just read the code.
- **[PWN.College — Heap Exploitation](https://pwn.college/)** (platform, same path) — focus on: glibc malloc internals, the foundation without which no heap attack makes sense.
- **[CryptoCat — Heap Exploitation](https://www.youtube.com/c/cryptocat23)** (video series, deep) — focus on: seeing chunk manipulation visually; heap is hard to grasp by reading alone.
- **[pwnable.tw + Nightmare (Heap section)](https://pwnable.tw/)** (challenges) — focus on: solve intermediate heap challenges after each technique from how2heap. Expect to spend days on one challenge — that's normal.

---

## Phase 5 — Specialization + Building Reputation
**Ongoing · Turning skill into professional value**
**Goal:** aim the skill at firmware/IoT and build a portfolio that actually gets you hired.

### Applied specialization
- [ ] Aim the skill at **firmware / embedded exploitation** — where PWN meets OT and IoT security, making you the offensive engine for that segment.
- [ ] Master **Reverse Engineering** with **[Ghidra](https://ghidra-sre.org/)** (free, from the NSA; commercial alternative: IDA Pro).

### Building reputation (most important for hiring)
- [ ] 🏁 Build a **portfolio**: publish a write-up for every challenge you solve. In this field, practical proof (CTFs + published write-ups) matters far more than certificates.

### Certificates (optional, by priority)
- [ ] PWN.College completion certificates — enough for the start, recognized in the community.
- [ ] **OSED** (OffSec Exploit Developer) — the reference certificate, a distant goal not a starting point. Advanced and costly; don't consider it before Phase 3–4.

### 📚 Resources
- **Practical Binary Analysis — Dennis Andriesse** (book, reference) — focus on: deep reverse engineering and ELF analysis at a professional level. Read it in this phase, not before — the disassembly and dynamic analysis sections.
- **[Ghidra (NSA)](https://ghidra-sre.org/)** (tool, free) — focus on: disassembling a binary and reading decompiled code. Your bridge to analyzing OT/IoT firmware.
- **[Exploit-DB](https://www.exploit-db.com/) + reading write-ups** (reference, real CVEs) — focus on: stop with artificial challenges and study real vulnerabilities. Pick a CVE in open-source software and try to understand/reproduce it yourself — that's real Vulnerability Research.
- **firmware emulation (search: "FirmAE") + "embedded exploitation"** (video, for specialization) — focus on: firmware emulation, extraction (binwalk), and analysis. This is where your skill gains direct commercial value.

---

> **Methodology note:** the real measure of success in this field isn't the number of lessons, but the number of challenges solved and write-ups written. Phases 2–3 (Assembly and first exploitation) are the hardest psychologically — getting past them means you're truly in.
