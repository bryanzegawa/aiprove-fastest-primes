#!/usr/bin/env bash
set -e
# Static binary: runs on any x86_64 Linux without libc-version surprises.
# No -march=native: the committed binary must run on the grader's machine.
gcc -O3 -std=c11 -static primes.c -o primes
