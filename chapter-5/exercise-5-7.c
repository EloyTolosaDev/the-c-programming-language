#include <stdio.h>
#include <string.h>

/**
 * Exercise 5-7. Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage. How much faster is the
 * program?
 *
 * Obviously, there will be a huge difference in between these two functions.
 * The old one has to allocate for a chunk of memory **every time** a new line
 * is read from strdin, while the second one it is already provided the
 * memory allocated to store every line.
 *
 * Allocating memory is quite a huge task, which makes a huge difference here.
 * */

#define MAXLEN 1000

int get_line(char *s, int lim);

int get_line(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
	s[i] = c;
    if (c == '\n') {
	s[i] = c;
	++i;
    }
    s[i] = '\0';
    return i;
}

int readlines_new(char *lineptr[], char p[], int maxlines) {
    int len, nlines;
    char line[MAXLEN];
    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
	if (nlines >= maxlines)
	    return -1;
	else {
	    line[len - 1] = '\0'; /* delete newline */
	    strcpy(p, line);
	    lineptr[nlines++] = p;
	}
    return nlines;
}
