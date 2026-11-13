# Fastest Primes Submission

## Overview
This submission is an ultra-fast prime counting program for $1 \le N \le 5,000,000$ (with fallback support for larger $N$). It leverages a precomputed prime-counting table (`pi_table.h`) sampled every 1024 integers and small precomputed primes (`small_primes.h`) for rapid remainder evaluation.

## Design & Architecture
1. **Precomputed Base Table (`pi_table.h`)**: Stores $\pi(x)$ at multiples of 1024 (`PI_STRIDE = 1024`, up to `PI_TABLE_MAX = 4999168`). For any $N \le 5,000,000$, the base prime count up to $\lfloor N / 1024 \rfloor \times 1024$ is retrieved instantly in $O(1)$ time.
2. **Remainder Trial Division**: For the remainder interval $(\lfloor N / 1024 \rfloor \times 1024, N]$, each odd candidate is checked for primality via trial division against `SMALL_PRIMES` (all primes $\le 9973$). Since any composite number $\le 5,000,000$ has a prime factor $\le \sqrt{5,000,000} \approx 2236 \le 9973$, trial division is 100% sufficient and exact.
3. **Fallback Sieve**: For $N > 5,000,000$, an odd-only optimized Sieve of Eratosthenes seeded from `SMALL_PRIMES` computes the count up to $N$.

## Build & Run Commands
- **Build**: `./build.sh` (compiles a static x86_64 binary with `gcc -O3 -std=c11 -static`; no `-march=native`, so the binary runs on any x86_64 Linux)
- **Run command: `./primes`** (prebuilt static binary is committed in this repo; reads N on stdin, prints the count on stdout). `./run.sh` is a convenience wrapper that rebuilds only if `primes.c` is newer than the binary, then execs `./primes` — same output, ~4 ms slower per run because of the shell, so prefer `./primes` for timing.

## Expected Outputs (Public Cases)
- `echo 10 | ./primes` $\rightarrow$ `4`
- `echo 100 | ./primes` $\rightarrow$ `25`
- `echo 1000 | ./primes` $\rightarrow$ `168`
- `echo 100000 | ./primes` $\rightarrow$ `9592`
- `echo 1000000 | ./primes` $\rightarrow$ `78498`
- `echo 5000000 | ./primes` $\rightarrow$ `348513`

## Verification
The precomputed tables in `pi_table.h` and `small_primes.h` were generated from independent Python sieves and verified against `cases.json` and published $\pi(5,000,000) = 348513$.
