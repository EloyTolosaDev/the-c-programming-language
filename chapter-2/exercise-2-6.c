#include <stdio.h>

/*
 * Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n
 * bits that begin at position p set to the rightmost n bits of y, leaving the
 * other bits unchanged.
 * */
#define BYTE_BITSIZE 8
#define UINT_SIZE sizeof(unsigned int) * BYTE_BITSIZE

unsigned int setbits(unsigned x, int p, int n, unsigned int y);

int main() {
    unsigned int x, y;
    x = 0;
    y = 7;
    printf("For x=%u and y=%u, setbits(x,3,3,y) returns: %u\n", x, y,
	   setbits(x, 3, 3, y));
    return 0;
}

unsigned int setbits(unsigned x, int p, int n, unsigned int y) {
    /* Basically, we get the n mostrighmost bits of 'y', and set them to the n
     * bits of x, starting from position p, letting the rest unchanged */
    int k = UINT_SIZE - n;
    unsigned int mask = (y << k);
    mask = mask >> (UINT_SIZE - p - 1);
    return x | mask;
}
