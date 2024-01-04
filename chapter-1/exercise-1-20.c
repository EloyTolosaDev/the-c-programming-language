#include <stdio.h>

/*
 * Exercise 1-20.
 * Write a program detab that replaces tabs in the input with the
 * proper number of blanks to space to the next tab stop. Assume a fixed set of
 * tab stops, say every n columns.
 * Should n be a variable or a symbolic parameter?
 * */

/*
 * I didn't understand the exercise, but found out this explanation
 * in SO: https://stackoverflow.com/a/23583324
 * Hope this helps you out as it did to me.
 * */

#define TABSIZE 5
#define BUFSIZE 1024

/*
 * This looked very clean to me. I saw it in a SO post here:
 * https://stackoverflow.com/q/23583252
 * */
#define TAB '\t'
#define SPACE ' '

int getnewline(char line[], int length);

int main() {

    int len;
    char buffer[BUFSIZE];      /* Buffer where to read the input */
    char finalBuffer[BUFSIZE]; /* Buffer where to copy the input substituting
				  the tabs with spaces */
    while ((len = getnewline(buffer, BUFSIZE)) > 0) {
	int bi;	 /* Buffer index */
	int fbi; /* Final buffer index */
	bi = fbi = 0;
	for (int bi = 0; buffer[bi] != '\0'; ++bi) {
	    // when we find a tab, we must find the modulo
	    // of the index with the tabsize. The result means the amount of
	    // spaces we need to rest to the tabsize to add to get to the next
	    // tab stop.
	    if (buffer[bi] == TAB) {
		int nspaces = TABSIZE - (bi % TABSIZE);
		/* Insert the desired spaces */
		for (int j = 0; j < nspaces; ++j) {
		    finalBuffer[fbi + j] = SPACE;
		}
		fbi += nspaces - 1;
	    } else {
		finalBuffer[fbi] = buffer[bi];
	    }
	    ++fbi;
	}
	printf("%s", finalBuffer);
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
