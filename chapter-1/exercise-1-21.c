#include <stdio.h>

/*
 * Exercise 1-21. Write a program entab that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. Use the same
 * tab stops as for detab. When either a tab or a single blank would suffice to
 * reach a tab stop, which should be given preference?
 * */

#define TABSIZE 4
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
				  spaces with tabs */
    int state = 0;	       /* If we did find a space (1) or not (0) */
    int spaces = 0;	       /* Amount of spaces found consecutivelly */
    while ((len = getnewline(buffer, BUFSIZE)) > 0) {
	int bi;	 /* Buffer index */
	int fbi; /* Final buffer index */
	bi = fbi = 0;
	while (buffer[bi] != '\0') {
	    if (buffer[bi] == SPACE) {
		/* If we find a space, we set the state to found,
		 * and start counting spaces until we find a non space
		 * character */
		if (state == 0)
		    state = 1;
		++spaces;
	    } else {
		if (state == 1) { /* We could write if(state) */

		    /* When we find a non space character, we calculate
		     * the amount of tabs and spaces needed to fill */
		    int ntabs = spaces / TABSIZE;
		    int nspaces = spaces % TABSIZE;

		    for (int i = 0; i < ntabs; ++i)
			finalBuffer[fbi + i] = TAB;
		    fbi += ntabs;
		    for (int i = 0; i < nspaces; ++i)
			finalBuffer[fbi + i] = SPACE;
		    fbi += nspaces;

		    /*Reset state and space number count*/
		    spaces = 0;
		    state = 0;
		}
		finalBuffer[fbi] = buffer[bi];
		/* We increment fbi index only if we found a non-space
		 * character after a series of spaces
		 * */
		++fbi;
	    }
	    ++bi;
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
