#include <stdio.h>

/*
 * Exercise 1-22. Write a program to ``fold'' long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column.
 * */

#define FOLDSIZE 40
#define BUFSIZE 1024

#define IN 1  /* Inside of a word */
#define OUT 0 /* Outside of a word */

#define TAB '\t'
#define SPACE ' '

int getnewline(char line[], int length);

int main() {

    int len;
    int state;
    int wordIndex; /* Stores the index of the first character of the current
    word */
    char buffer[BUFSIZE];      /* Buffer where to read the input */
    char finalBuffer[BUFSIZE]; /* Buffer where to copy the final input */

    state = OUT;
    while ((len = getnewline(buffer, BUFSIZE)) > 0) {
	if (len > FOLDSIZE) {
	    int bi;
	    bi = 0;
	    while (buffer[bi] != '\0') {

		/* We found a word */
		if (buffer[bi] != TAB && buffer[bi] != SPACE) {
		    if (state == OUT) {
			state = IN;
			wordIndex = bi;
		    }
		} else {
		    /* We were inside a word and we exited it */
		    if (state == IN) {
			state = OUT;
		    }
		}

		/* When we reach the end of the line, we need to add a
		 * newline character and the character on the 'bi' index,
		 * and then continue iterating the array */
		if ((bi > 0) && (bi % (FOLDSIZE - 1) == 0)) {

		    /* We somehow need to take into account:
		     * - What happens if we finished the line before
		     * finishing a whole word?
		     * - What do we do if we finished a line at the same
		     * time we finished a word? What do we do with the space
		     * after it?
		     * */

		    /* To check if we are inside of a word, we will do
		     * similar to the example on page 22 of the book, same
		     * as I did in the exercise 1-12. I'm defining two
		     * symbolic constants, IN and OUT to check if we're
		     * inside or outside a word.
		     *
		     * If we are inide a word, given that we also are at the
		     * end of the line, we are going to not split the word
		     * into syllables, which would be much out of our scope.
		     * Instead, we will write the whole word into the next
		     * line, and write the newline right before it.
		     *
		     * For this, we we defined a variable that will store
		     * the index before the start of the word so we know
		     * when and where to copy into the new buffer.*/
		    if (state == IN) {
			int offset = bi - (wordIndex - 1);
			finalBuffer[bi - offset] = '\n';
		    } else {
			/* And the easiest example is if we are at the end of
			 * the line and there is a space. In this case, we will
			 * remove the space and just put a new line and continue
			 * with the next word
			 * */
			if (buffer[bi] == SPACE || buffer[bi] == TAB) {
			    buffer[bi] = '\n';
			}
		    }
		}

		finalBuffer[bi] = buffer[bi];
		++bi;
	    }
	}
	printf("%s\n", finalBuffer);
    }
}

/*
 * We take getnewline function from previous exercises
 * */
int getnewline(char line[], int length) {

    int c, i; /* Current char and current index */
    // populate 'line' until newline or EOF found or limit-1 reached
    for (i = 0; i < length - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
	line[i] = c;
    }
    // add '\n' to 'line' as \n is part of the line written to stdin
    if (c == '\n') {
	line[i] = c;
	++i;
    }
    // null character, needed for C to understand than line is a String
    line[i] = '\0';
    return i;
}
