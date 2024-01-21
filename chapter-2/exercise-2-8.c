#include <math.h>
#include <stdio.h>

/*
 * Exercise 2-8. Write a function rightrot(x,n) that returns the value of the
 * integer x rotated to the right by n positions.
 * */

/*
 * For what I can understand of this exercise, we want to rotate, keeping the
 * roatated bits from the right to the left. This means that, if we wanted to
 * rotate the number 0100 to the right 3 positions, the number would be 1000.
 * */

#define BYTE_BITSIZE 8
#define UINT_SIZE sizeof(unsigned int) * BYTE_BITSIZE

unsigned int rightrot(unsigned x, int n);

int main() {
    unsigned int x;

    x = 4;
    printf("rightrot(%u, 3)=%u\n", x, rightrot(x, 3));
    return 0;
}

unsigned int rightrot(unsigned x, int n) {
    int i;
    for (i = 0; i < n; i++) {
	/* If we have a 1 at the end of the number, we want to put the number at
	 * the leftmost part of the same.
	 *
	 * A number with a 1 at the rightmost is **always** odd.
	 * */
	if (x % 2 != 0) {
	    /* We shift the number 1 position to the right, and OR
	     * it with 2^n being n the size in bits of the number.
	     * */
	    x = (x >> 1) | (unsigned int)pow(2, UINT_SIZE);
	} else {
	    x = x >> 1;
	}
    }
    return x;
}
