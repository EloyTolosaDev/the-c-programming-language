#include <stdio.h>

/* Exercise 1-16. Revise the main routine of the longest-line program so it will
 * correctly print the length of arbitrary long input lines, and as much as
 * possible of the text.*/

/*
 * To make this, what we have to do is modify the main function and the
 * getnewline function. First, we'll make 'getnewline' stop if and only if a new
 * line was found, or the MAXLINE limit is reached. After reading the line, we
 * will check if the last character is a new line. If it's not, we will read
 * again, repeating the process untill the whole text is printed.
 *
 * */

/*
 * This is how the program gets.
 * */

#define MAXLINE 1000 /* max input line length */

/* Auxiliar function definitions (I think this should go in a .h file) */
int getnewline(char line[], int length);
void copy(char from[], char to[]);

int main() {
    int len;		     /* Current line length (until MAXLINE) */
    int totalLen;	     /* Total current line length (above MAXLINE) */
    int max;		     /* Current max line length found */
    int keep;		     /* Keep on reading the same long line*/
    char line[MAXLINE];	     /* Current read line */
    char beginning[MAXLINE]; /* Temp array to keep the beginning of the line */
    char longest[MAXLINE];   /* Current longest line */

    max = 0;
    len = 0;
    totalLen = 0;
    while ((len = getnewline(line, MAXLINE)) > 0) {

	/* If we havent finished reading the line, we countinue */
	keep = (line[len - 1] != '\n');
	if (keep) {
	    copy(line, beginning);
	}
	totalLen += len;

	if (keep == 0) {
	    if (totalLen > max) {
		max = totalLen;
		totalLen = 0;
		copy(line, longest);
	    }
	}
    }

    /* Min a line was provided to the program */
    if (max > 0) {
	printf("Longest line was: %s\n", beginning);
	printf("With a length of %d characters. \n", max);
    }

    return 0;
}

/*
 * Reads 'length' number of characters from stdin into 'line' array
 * Returns the read length
 */
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

void copy(char from[], char to[]) {
    int i, c;
    i = 0;
    c = from[i];
    while (c != '\0') {
	to[i] = c;
	++i;
	c = from[i];
    }
}
