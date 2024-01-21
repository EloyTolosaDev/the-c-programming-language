#include <math.h>
#include <stdio.h>

/*
 * Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the
 * rightmost 1-bit in x. Explain why. Use this observation to write a faster
 * version of bitcount.
 * */

/*
 * The reason this works is because, when you subtract 1 from a number, you
 * change to 0 the rightmost 1, and transform the rest of the numbers to the
 * right to 1. THen, when you AND it with the original number, because the
 * rightmost 1 turned into 0, the result returns a 0 in the original rightmost
 * 1, leaving the 1ns in the left uncganged.
 * */

#define BYTE_BITSIZE 8
#define UINT_SIZE sizeof(unsigned int) * BYTE_BITSIZE

unsigned int bitcount(unsigned x);

int main() {
    unsigned int x;
    x = 2456; // 100110011000 = 5 bits set to 1
    printf("bitcount(%u)=%u\n", x, bitcount(x));
    return 0;
}

/*
 * To count how many bits set to 1 are in a number, we just have to perform
 * x &= (x-1) until the number is 0.
 * */
unsigned int bitcount(unsigned x) {
    int i;
    for (i = 0; i < UINT_SIZE && x != 0; i++) {
	x &= (x - 1);
    }
    return i;
}
