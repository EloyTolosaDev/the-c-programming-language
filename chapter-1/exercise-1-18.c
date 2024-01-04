#include <stdio.h>

/*
 * Exercise 1-18. Write a program to remove trailing blanks and tabs from each
 * line of input, and to delete entirely blank lines.
 *
 * I solved this exercise making use of an auxiliary function, but I will post
 * another solution for the same exercise without using one, just to have more
 * completeness.
 * */

#define MAXLINE 1000 /* max input line length */

/* Auxiliar function definitions (I think this should go in a .h file) */
int getnewline(char line[], int length);
int clearline(char line[], int len);

int main() {
    int len;		/* Current line length (until MAXLINE) */
    char line[MAXLINE]; /* Current read line */

    len = 0;
    while ((len = getnewline(line, MAXLINE)) > 0) {
	if (clearline(line, len) > 0) {
	    printf("%s", line);
	}
    }

    return 0;
}

/*
 * This function Removes trailing blanks and tabs
 *
 * It is not compulsory to solve it like this, but I found it usefull given that
 * the book already tought you how to make functions.
 *
 * This function returns the length of the line AFTER fixing it. So, if the
 * function returns 0, that means the line is a blank like, and we can thus
 * remove it. This way it has double functioinality
 * */

int clearline(char line[], int len) {
    int i;
    int lc; /* Last non-blank character index */

    for (i = len - 2; i >= 0 && lc == 0; --i) {
	if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {
	    lc = i;
	}
    }

    // wherever we put the \0, means the string ended.
    line[lc] = '\0';
    return lc;
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
