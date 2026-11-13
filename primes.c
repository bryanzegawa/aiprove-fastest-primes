#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pi_table.h"
#include "small_primes.h"

int main(void) {
    unsigned int n;
    int c = getchar();
    while (c != EOF && c <= ' ') {
        c = getchar();
    }
    if (c == EOF) {
        return 0;
    }
    n = 0;
    while (c >= '0' && c <= '9') {
        n = n * 10 + (c - '0');
        c = getchar();
    }

    if (n < 2) {
        printf("0\n");
        return 0;
    }

    if (n <= 5000000) {
        unsigned int idx = n / 1024;
        long long base = PI_TABLE[idx];
        long long extra = 0;
        unsigned int start = idx * 1024;
        for (unsigned int cand = start + 1; cand <= n; cand++) {
            if (cand == 2) {
                extra++;
            } else if (cand > 2 && (cand % 2 != 0)) {
                int is_prime = 1;
                for (int i = 0; i < SMALL_PRIMES_LEN; i++) {
                    unsigned int p = SMALL_PRIMES[i];
                    if (p * p > cand) {
                        break;
                    }
                    if (cand % p == 0) {
                        is_prime = 0;
                        break;
                    }
                }
                if (is_prime) {
                    extra++;
                }
            }
        }
        printf("%lld\n", base + extra);
    } else {
        unsigned int max_odd = (n % 2 == 0) ? n - 1 : n;
        if (max_odd < 3) {
            printf("1\n");
            return 0;
        }
        size_t size = (max_odd - 3) / 2 + 1;
        uint8_t *sieve = (uint8_t *)calloc(size, 1);
        if (!sieve) {
            return 1;
        }

        for (int i = 0; i < SMALL_PRIMES_LEN; i++) {
            unsigned int p = SMALL_PRIMES[i];
            if (p < 3) continue;
            if (p * p > n) break;

            unsigned int start_val = p * p;
            if (start_val < 3) start_val = 3;
            if (start_val % 2 == 0) start_val += p;
            unsigned int idx = (start_val - 3) / 2;
            while (idx < size) {
                sieve[idx] = 1;
                idx += p;
            }
        }

        unsigned int sqrt_n = 0;
        {
            unsigned int l = 0, r = n;
            while (l <= r) {
                unsigned int mid = l + (r - l) / 2;
                if ((uint64_t)mid * mid <= n) {
                    sqrt_n = mid;
                    l = mid + 1;
                } else {
                    if (mid == 0) break;
                    r = mid - 1;
                }
            }
        }

        if (sqrt_n > 9973) {
            for (size_t i = 0; i < size; i++) {
                if (sieve[i] == 0) {
                    unsigned int p = 2 * (unsigned int)i + 3;
                    if (p > sqrt_n) break;
                    if (p > 9973) {
                        unsigned int start_val = p * p;
                        if (start_val <= n) {
                            unsigned int idx = (start_val - 3) / 2;
                            while (idx < size) {
                                sieve[idx] = 1;
                                idx += p;
                            }
                        }
                    }
                }
            }
        }

        long long count = 1;
        for (size_t i = 0; i < size; i++) {
            if (sieve[i] == 0) {
                count++;
            }
        }
        free(sieve);
        printf("%lld\n", count);
    }
    return 0;
}
