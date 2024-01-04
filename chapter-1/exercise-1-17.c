#include <stdio.h>

/*
 * Exercise 1-17. Write a program to print all input lines that are longer than
 * 80 characters.
 *
 * This solution is based on the solution of the previous exercise.
 * */

#define MAXLINE 1000 /* max input line length */
#define THRESHOLD 80 /* length in which we will print lines */

/* Auxiliar function definitions (I think this should go in a .h file) */
int getnewline(char line[], int length);

int main() {
    int len;		/* Current line length (until MAXLINE) */
    char line[MAXLINE]; /* Current read line */

    len = 0;
    while ((len = getnewline(line, MAXLINE)) > 0) {
	if (len > THRESHOLD) {
	    printf("%s", line);
	}
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
