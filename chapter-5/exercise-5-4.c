#include <stdio.h>
#include <stdlib.h>

/**
 * Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t
 * occurs at the end of the string s, and zero otherwise.
 * */

/**
 * Macro that returns Yes or No depending on the boolean value
 * passed per parameter
 * */
#define BOOL(a) (a == 1) ? "Yes" : "No"

int strend(char *s, char *t);

int main(int argc, char *argv[]) {

    char *s = "Hello world";
    char *t = "world";
    char *res = BOOL(strend(s, t));
    printf("Does the word '%s' occur at the end of '%s'?: %s\n", t, s, res);

    return EXIT_SUCCESS;
}

int strend(char *s, char *t) {
    char *bt = t; /* save a copy of the initial position of t */
    while (*s)
	s++; /* go to the end of s*/
    while (*t)
	t++; /* go to the end of t */
    while (*s == *t)
	s--, t--;
    /**
     * The function returns 1 if, after looping s and t from end to beginning,
     * the final position of t is exactly the same as the copy saved at the
     * beginning of the function. This means that all characters were equal,
     * from the end of s, until the beginning of t.
     * */
    return ++t == bt;
}
