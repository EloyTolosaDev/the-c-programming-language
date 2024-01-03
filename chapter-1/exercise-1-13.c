#include <stdio.h>

/*
 * Exercise 1-13. Write a program to print a histogram of the lengths of words
 * in its input. It is easy to draw the histogram with the bars horizontal; a
 * vertical orientation is more challenging.
 * */
#define IN 1
#define OUT 0

int main() {

    int c, state, cc;
    state = OUT;
    cc = 0;
    while ((c = getchar()) != EOF) {
	if (c == ' ' || c == '\t' || c == '\n') {
	    if (state == IN) {
		/*
		 * When word is finished, # "cc" (character count) times
		 * */
		printf(" (%d chars) | ", cc);
		for (int i = 0; i < cc; ++i) {
		    printf("#");
		}
		printf("\n");
		state = OUT;
		cc = 0;
	    }
	} else if (state == OUT) {
	    state = IN;
	}
	printf("%c", c);
	++cc;
    }

    return 0;
}
