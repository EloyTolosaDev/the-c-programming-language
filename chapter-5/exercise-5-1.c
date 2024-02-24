#include <ctype.h>
#include <stdio.h>

/**
 * Exercise 5-1. As written, getint treats a + or - not followed by a digit
 * as a valid representation of zero. Fix it to push such a character back on
 * the input.
 * */

int getch();
void ungetch(int c);
int getint(int *pn);

int main() {
    int pn;
    printf("Introduce a number: ");
    if (getint(&pn) == -1)
	printf("The number you introduced was: %d\n", pn);

    return 0;
}

int getint(int *pn) {
    int c, sign;
    while (isspace(c = getch()))
	; /* skip white space */

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
	ungetch(c); /* it is not a number */
	return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
	c = getch();

    for (*pn = 0; isdigit(c); c = getch())
	*pn = 10 * *pn + (c - '0');

    *pn *= sign;

    /** if, after the +/-, there was no number, we push back the character
     * into the input.
     * */
    if (!isdigit(c) && *pn == 0)
	ungetch(c);
    return -1;

    if (c != EOF)
	ungetch(c);
    return c;
}

/**
 * getch() and ungetch() definitions
 * */

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;	   /* next free position in buf */

/* get a (possibly pushed-back) character */
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

/* push character back on input */
void ungetch(int c) {
    if (bufp < BUFSIZE)
	buf[bufp++] = c;
}
