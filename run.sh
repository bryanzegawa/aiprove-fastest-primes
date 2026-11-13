#!/usr/bin/env bash
set -e
if [ ! -f ./primes ] || [ primes.c -nt ./primes ]; then
    ./build.sh
fi
exec ./primes
