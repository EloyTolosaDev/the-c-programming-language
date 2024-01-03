#include <bits/types.h>
#include <stdio.h>

/*
 * Exercise 1-12. Write a program that prints its input one word per line.
 * */

/*
 * I am basing this solution in the example on page 22 of the book.
 * It defines two symbolic constants to check if we are inside of a word
 * or outside.
 *
 * The logic is, if we are inside a word, and we encounter a space, a tab or a
 * new line, the word count increases.
 * */

#define IN 1
#define OUT 0

int main() {

    int c, state, wc;
    state = OUT;
    wc = 0;
    while ((c = getchar()) != EOF) {
	if (c == ' ' || c == '\t' || c == '\n') {
	    if (state == IN) {
		++wc;
		state = OUT;
	    }
	} else if (state == OUT) {
	    state = IN;
	}
    }

    printf("Word count: %d\n", wc);

    return 0;
}
