#include <stdio.h>
#include <string.h> /* for strlen() */

/**
 * Exercise 4-7. Write a routine ungets(s) that will push back an entire string
 * onto the input. Should ungets know about buf and bufp, or should it just use
 * ungetch?
 * */

#define MAXLEN 1000

int getch();
void ungetch(int c);
void ungets(char c[]);

int main() {

    char s[] =
	"This is a string we're going to read into another buffer, using"
	" ungets() method to see if it works well. If the string is too large"
	" it should get cut at the left.";
    char t[MAXLEN];

    /**
     * put s into the internal buffer and read using getch() into buffer t[]
     * */
    ungets(s);
    int i, c;
    for (i = 0; (c = getch()) != EOF; i++)
	t[i] = c;

    printf("%s\n", t);

    return 0;
}

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

void ungets(char s[]) {
    int len = strlen(s);
    for (; len > 0;)
	ungetch(s[--len]);
}
