#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Exercise 5-13. Write the program tail, which prints the last n lines of its
 * input. By default, n is set to 10, let us say, but it can be changed by an
 * optional argument so that tail -n prints the last n lines.
 * The program should behave rationally no matter how unreasonable the input or
 * the value of n. Write the program so it makes the best use of available
 * storage; lines should be stored as in the sorting program of Section 5.6, not
 * ina two-dimensional array of fixed size.
 * */

#define DEFAULT 10
#define ERROR -1
#define MAXLINES 1000000
#define MAXLINELENGTH MAXLINES

/**
 * This is an fixed-array of pointers to strings. Each pointer will point to a
 * input line
 * */
char *buffer[MAXLINES];

int get_argument(char **args, const char *arg) {
    int n;
    /**
     * Skip first arguments until we find the argument '-n' or we do not find
     * anything, in this case we return 0;
     * */
    while (*args != NULL && strcmp(*args, arg) != 0)
	*args++;
    /* *args == NULL mens we finished reading command line args */
    if (*args == NULL) {
	n = DEFAULT;
    } else {
	/**
	 * Check if 'n' is set, i.e: "tail -n" skipping initializing 'n'
	 * */
	*args++;
	if (*args == NULL) {
	    printf("[error]: no value set for flag '%s'.\n", arg);
	    n = ERROR;
	} else if (!isdigit(**args)) {
	    printf("[error]: no value set for flag '%s'.\n", arg);
	    n = ERROR;
	} else {
	    n = atoi(*args);
	}
    }
    return n;
}

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;	 /* next free position */

char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
	allocp += n;
	return allocp - n;
    } else
	return 0; /* A pointer with value 0 is NULL */
}

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

int main(int argc, char **args) {

    int n = get_argument(args, "-n");
    printf("[debug]: Value of n=%d\n", n);

    /**
     * read lines from input and copy them into our line buffer
     * */
    char line[MAXLINELENGTH], *p;
    int len, lines;
    while ((len = get_line(line, MAXLINELENGTH)) > 0) {

	/**
	 * We're using alloc from page 91 of the book
	 * */
	if ((p = alloc(len)) == NULL) {
	    printf("[error] Error allocating space for pointer\n");
	    return 1;
	}

	/**
	 * You have to do this so C knows that the end of the line
	 * is the end of the string
	 * */
	line[len - 1] = '\0';

	strcpy(p, line);
	buffer[lines++] = p;
    }

    /**
     * To print the last n lines, you subtract 'n' to the buffer, and then you
     * read them in order incrementing the buffer.
     * */
    printf("\n");
    for (int i = lines - n; buffer[i] != NULL && n-- > 0; i++)
	printf("[buffer(%d)]: %s\n", i, buffer[i]);

    return EXIT_SUCCESS;
}
