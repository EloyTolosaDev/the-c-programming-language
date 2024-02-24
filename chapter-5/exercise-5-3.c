#include <stdio.h>

/**
 * Exercise 5-3. Write a pointer version of the function strcat that we showed
 * in Chapter 2: strcat(s,t) copies the string t to the end of s.
 * */

#define MAXLEN 1000

void strcat_p(char *s, char *t);

int main() {
    char s[MAXLEN] = "Hello ";
    char t[] = "World!\n";

    strcat_p(s, t);

    printf("%s\n", s);

    return 0;
}

void strcat_p(char *s, char *t) {
    while (*s)
	s++;
    while (*s++ = *t++)
	;
}
