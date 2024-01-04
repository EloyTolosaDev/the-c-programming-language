#include <stdio.h>

/*
 * Exercise 1-19. Write a function reverse(s) that reverses the character string
 * s. Use it to write a program that reverses its input a line at a time.
 * */

#define MAXLINE 1000 /* max input line length */

/* Auxiliar function definitions (I think this should go in a .h file) */
int getnewline(char line[], int length);
void reverse(char input[], char reversed[], int len);

int main() {
    int len;		    /* Current line length (until MAXLINE) */
    char line[MAXLINE];	    /* Current read line */
    char reversed[MAXLINE]; /* Reversed string */

    len = 0;
    while ((len = getnewline(line, MAXLINE)) > 0) {
	reverse(line, reversed, len);
	printf("Here's your reversed string: \t%s \n", reversed);
    }

    return 0;
}

void reverse(char input[], char reversed[], int len) {
    int i, j;
    i = 0;
    j = len - 1;
    while (j >= 0 && i < len) {
	reversed[j] = input[i];
	++i;
	--j;
    }
}

/*
 * Reads 'length' number of characters from stdin into 'line' array
 * Returns the read length
 */
int getnewline(char line[], int length) {

    printf("Please, write here the string to reverse: ");

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
