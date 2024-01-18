#include <stdio.h>

/*
 * Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits
 * that begin at position p inverted (i.e., 1 changed into 0 and vice versa),
 * leaving the others unchanged.
 * */

#define BYTE_BITSIZE 8
#define UINT_SIZE sizeof(unsigned int) * BYTE_BITSIZE

unsigned int invert(unsigned x, int p, int n);

int main() {
    unsigned int x;

    x = 77;
    printf("invert(%u,4,3)=%u\n", x, invert(x, 4, 3));
    return 0;
}

unsigned int invert(unsigned x, int p, int n) {
    unsigned int mask = ~0 << (UINT_SIZE - p - 1);
    mask = mask >> (UINT_SIZE - n);
    mask = mask << (p - n + 1);
    printf("    [invert] mask = %u\n", mask);
    return x ^ mask;
}
