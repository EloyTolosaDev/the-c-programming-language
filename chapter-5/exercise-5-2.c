#include <ctype.h>
#include <stdio.h>

/**
 * Exercise 5-2. Write getfloat, the floating-point analog of getint. What type
 * does getfloat return as its function value?
 * */

int getch();
void ungetch(int c);
int getfloat(float *f);

int main() {
    float f;
    printf("Introduce a number: ");
    if (getfloat(&f))
	printf("The number you introduced was: %.6f\n", f);

    return 0;
}

int getfloat(float *f) {

    int c, power;
    float flt;
    /* skip whitespaces and tabs */
    while (c = getch(), c == ' ' || c == '\t')
	;

    /* check sign and read char if necessary */
    int sign = (c == '-') ? -1 : 1;
    if (c == '-')
	c = getch();

    /* get integer part  */
    while (isdigit(c))
	*f = (*f) * 10 + (c - '0'), c = getch();

    if (c == '.')
	c = getch();

    /* get fractional part */
    for (power = 1; isdigit(c); power *= 10) {
	flt = flt * 10 + (c - '0');
	c = getch();
    }

    *f = sign * (*f + flt / power);

    if (c == EOF)
	return EOF;

    return 1;
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
