#include <stdio.h>

/*
 * Exercise 1-14. Write a program to print a histogram of the frequencies of
 * different characters in its input
 * */

// NOTE: Change space before and after operational signs

#define SIZE 255

int main(void) {

    int c;
    char chars[SIZE];
    for (int i = 0; i < SIZE; ++i) {
	chars[i] = 0;
    }

    while ((c = getchar()) != EOF) {
	// increase counter at the 'c' character array position
	/* c - BEGIN is an index between 0 and 126-33=93 */
	++chars[c];
    }

    for (int i = 0; i < SIZE; ++i) {
	// only print characters that have more than 1 count
	if (chars[i] > 0) {
	    printf("%c | ", i);
	    for (int j = 0; j < chars[i]; ++j) {
		printf("#");
	    }
	    printf("\n");
	}
    }
}
