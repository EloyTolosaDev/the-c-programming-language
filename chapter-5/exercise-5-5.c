#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Exercise 5-5. Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument
 * strings. For example, strncpy(s,t,n) copies at most n characters of t to s.
 * */

#define MAXLEN 100

char *strncpy_s(char *dest, const char *s, int nchars);
char *strncat_s(char *dest, const char *s, int nchars);
int strncmp_s(const char *dest, const char *s, int nchars);

int main(int argc, char *argv[]) {

    char dest[MAXLEN], *src, *result;

    src = "Hello world!";
    printf("Copying %s into a buffer...\n", src);
    result = strncpy_s(dest, src, 50);
    printf("[strncpy_s] %s\n", result);

    src = " I'm writting this in a webpage!";
    printf("\nConcatenating %s and %s...\n", dest, src);
    /** realize that it does not matter how big the n in this function is
     * because it will read until s has ended.
     * In the case that s is smaller than n, only strlen(s) bytes will be
     * added.
     * */
    result = strncat_s(dest, src, 1234);
    printf("[strncat_s] %s\n", result);

    src = "Hello world!";
    printf("Comparing '%s' with '%s' to all its length...\n", dest, src);
    int res = strncmp_s(dest, src, 200);
    printf("[strncmp_s] %d\n", res);

    printf("Now we're going to compare the same strings, but only the first"
	   " 11 characters...\n");
    res = strncmp_s(dest, src, 11);
    printf("[strncmp_s] %d\n", res);

    /**
     * In this example case, we're going to compare the string "Hello world"
     * with itself, but removing the letter 'o' from "Hello world".
     *
     * The result will be -79, because the first character that differ are ' '
     * and 'o', and their difference in the ascii table is 32 (space) - 111 (o)
     * = -79.
     * */
    result = strncpy(dest, "Hell world!", 20);
    printf("Now, we're going to compare '%s' and '%s' entirely...", dest, src);
    res = strncmp_s(dest, src, 200);
    printf("[strncmp_s] %d\n", res);

    return EXIT_SUCCESS;
}

/**
 * In this type of functions, we always have to assume there's enough
 * space in the dest buffer.
 * */

int strncmp_s(const char *dst, const char *s, int nchars) {
    for (; nchars > 0 && *dst != '\0' && *s != '\0' && *dst == *s;
	 dst++, s++, nchars--)
	;

    if (*dst && !*s) /* dst is larger than s */
	return 1;
    else if (*s && !*dst) /* s is larger than dst */
	return -1;
    /* if they are the same lenth, compare the last character */
    return *dst - *s;
}

char *strncat_s(char *dest, const char *s, int nchars) {
    char *p = dest;
    while (*dest)
	dest++; /* go to the end of dest */
    for (; nchars > 0 && *s; nchars--, s++, dest++)
	*dest = *s;
    *++dest = '\0';

    return p;
}

char *strncpy_s(char *dest, const char *s, int nchars) {
    char *db = dest;
    for (; nchars > 0 && *s; nchars--, s++)
	*dest++ = *s;

    /* if s is shorter than nchars, we write up until nchars null terminators */
    while (nchars > 0)
	*dest++ = '\0', nchars--;

    return db;
}
