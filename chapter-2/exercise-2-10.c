#include <stdio.h>
#include <stdlib.h> /* Import to get EXIT_SUCCESS */
#include <string.h> /* Import to get strlen() */

/*
 * Exercise 2-10. Rewrite the function lower, which converts upper case letters
 * to lower case, with a conditional expression instead of if-else.
 * */

void lower(char s[]);

int main() {
    char s[] = "THE BIRD JUMPED FROM THE TREE AND FELL OFF";
    printf("The string before lower() is: %s\n", s);
    lower(s);
    printf("The string after lower() is: %s\n", s);

    return EXIT_SUCCESS;
}

void lower(char s[]) {
    for (int i = 0; i < strlen(s) - 1; i++) {
	/* NOTE: Asuming s only contains english alphabet letters */
	/* 65 is 'A' and 90 is 'Z'. Upper and lower letters are 32
	 * numbers appart in the ascii table:
	 * See: https://www.asciitable.com/ */
	(s[i] >= 65 && s[i] <= 90) ? s[i] += 32 : s[i];
    }
}
