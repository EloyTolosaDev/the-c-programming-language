#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Exercise 5-14. Modify the sort program to handle a -r flag, which indicates
 * sorting in reverse (decreasing) order. Be sure that -r works with -n
 * */

/**
 * Exercise 5-15. Add the option -f to fold upper and lower case together, so
 * that case distinctions are not made during sorting; for example, a and A
 * compare equal.
 * */

/**
 * Exercise 5-16. Add the -d (``directory order'') option, which makes
 * comparisons only on letters, numbers and blanks. Make sure it works in
 * conjunction with -f.
 * */

#define MAXLINES 5000	 /* max #lines to be sorted */
#define MAXLEN 1000	 /* max line length */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void quicksort(void *lineptr[], int left, int right,
	       int (*comp)(void *, void *));
int numcmp(char *, char *);

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

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = get_line(line, MAXLINES)) > 0) {
	if (nlines >= maxlines || (p = malloc(len)) == NULL) {
	    return -1;
	}
	line[len - 1] = '\0'; /* delete newline */
	strcpy(p, line);
	lineptr[nlines++] = p;
    }

    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    int i;
    for (i = 0; i < nlines; i++)
	printf("%s\n", lineptr[i]);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
	return -1;
    else if (v1 > v2)
	return 1;
    else
	return 0;
}

void quicksort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);
    if (left >= right) /* do nothing if array contains */
	return;	       /* fewer than two elements */
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
	if ((*comp)(v[i], v[left]) < 0)
	    swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last - 1, comp);
    quicksort(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void reverse(char *lines[]) {
    int i, j;
    for (j = 0; lines[j] != NULL; j++)
	;
    for (i = 0, j--; j > i; i++, j--) {
	swap((void **)lines, i, j);
    }
}

void to_lowercase(char *s) {
    while (*s) {
	/* range of uppercase characters */
	if (*s >= 65 && *s <= 90)
	    *s += 32;
	s++;
    }
}

#define FOLD(s)                                                                \
    for (int i = 0; s[i] != NULL; i++)                                         \
    to_lowercase(s[i])

int exercise_5_14_16(int argc, char **args) {

    int nlines; /* number of input lines read */
    int numeric, reversed, folded, directory;

    /**
     * loop through args so we can input flags in any order
     * */
    while (*args != NULL) {
	if (strcmp(*args, "-n") == 0)
	    numeric = 1;
	else if (strcmp(*args, "-r") == 0)
	    reversed = 1;
	else if (strcmp(*args, "-f") == 0)
	    folded = 1;
	else if (strcmp(*args, "-d") == 0)
	    directory = 1;

	*args++;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {

	/**
	 * In this case we will convert to lower case all the strings and then
	 * compare them so there's no distinctions
	 * */
	if (folded)
	    FOLD(lineptr);

	/**
	 * This line casts the functions numcmp and strcmp
	 * to a pointer function with void* parameters that return
	 * an int.
	 *
	 * Its important because the quicksort interface accepts only this type
	 * of functions.
	 * */
	quicksort((void **)lineptr, 0, nlines - 1,
		  (int (*)(void *, void *))(numeric ? numcmp : strcmp));

	if (reversed)
	    reverse(lineptr);

	writelines(lineptr, nlines);
	return 0;
    } else {
	printf("input too big to sort\n");
	return 1;
    }

    return 0;
}
