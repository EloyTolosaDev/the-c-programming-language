#include <stdio.h>  /* For printf() */
#include <string.h> /* For strlen() */

/**
 * Exercise 4-12. Adapt the ideas of printd to write a recursive version of
 * itoa; that is, convert an integer into a string by calling a recursive
 * routine.
 * */

#define MAXLEN 100

void itoa(int n, char s[]);
void reverse(char s[]);

int main() {
    int n = -1647823146;
    char s[MAXLEN];
    itoa(n, s);
    printf("itoa(%d)=%s with length of %lu.\n", n, s, strlen(s));

    return 0;
}

void reverse(char s[]) {
    int i, j, temp;
    for (i = 0, j = strlen(s) - 1; j > i; i++, j--)
	temp = s[i], s[i] = s[j], s[j] = temp;
}

void itoa(int n, char s[]) {

    /**
     * We will make use of the inner static property of C. When you declare a
     * static variable inside a function in C, the variable keeps track of the
     * state in between calls (recursive or not).
     *
     * So in this case, we will create a static variable to keep track of the
     * index of the string to put the values on.
     * */
    static int i = 0;
    static int sign = 0;

    if (sign == 0)
	sign = (n < 0) ? -1 : 1;

    if (n == 0) {
	/* reverse the string as we've put characters in reverse order */
	s[i++] = (sign == 1) ? '\0' : '-';
	s[i] = '\0';
	reverse(s);
    } else {
	/* calculate digit, put it in place and recalculate number */
	int d = n % 10;
	d = (d < 0) ? -d : d;
	s[i++] = d + '0';
	n /= 10;

	itoa(n, s);
    }
}
