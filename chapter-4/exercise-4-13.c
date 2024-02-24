#include <stdio.h>  /* for printf() */
#include <string.h> /* for strlen() */

/**
 * Exercise 4-13. Write a recursive version of the function reverse(s), which
 * reverses the string s in place.
 * */

void reverse_r(char s[]);

int main() {

    char s[] = "Hello world!";
    printf("String unchanged: %s\n", s);
    reverse_r(s);
    printf("String reversed: %s\n", s);

    return 0;
}

void reverse_r(char s[]) {
    static int i = 0;
    int j = strlen(s) - i - 1;
    if (j < i)
	return;

    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    i++;
    reverse_r(s);
}
