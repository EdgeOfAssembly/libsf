# Project Guidance for debug

## Best Practices
- C/C++: RAII/smart ptrs, no raw alloc. Latest std (C23/C++23 feats).
- Python: PEP8, venv, hints/docstrings.
- Asm: NASM, extensive comments, SIMD/unroll.
- All: Secure (no overflows), efficient (profile first).

## Tools/Install (Distro-Neutral)
- C/C++: GCC/binutils (Ubuntu: apt install build-essential; Fedora: dnf groupinstall "Development Tools"; macOS: brew install gcc; Arch: pacman -S base-devel).
- Python: 3.12+ (apt install python3; brew install python@3.12).
- Debug: Valgrind (apt install valgrind; brew install valgrind), GDB (apt install gdb; brew install gdb), cppcheck (apt install cppcheck; brew install cppcheck).
- Opt: perf (Linux kernel tools; apt install linux-tools-common), gprof (GCC flag).
- Asm: NASM (apt install nasm; brew install nasm).
- Analysis: pylint (pip install pylint).
- Fetch debug.h: wget/curl the link or search; include in project.

## QA/Debug/Opt
- QA: 80% test cov (GoogleTest/pytest), static analysis, reviews (DO-178C style: trace reqs).
- Debug: ASan/UBSan/TSan flags, asserts via debug.h (disabled in release).
- Opt: Profile (perf), vectorize (-ftree-vectorize), LTO (-flto).

Use in sessions: Paste prompt first, reference guidance.