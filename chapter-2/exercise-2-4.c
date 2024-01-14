#include <stdio.h>

/*
 * Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes
 * each character in s1 that matches any character in the string s2.
 * */

void squeeze(char s1[], char s2[]);

int main() {
    printf("In this program, we are going to use the 'squeeze' function to "
	   "remove all the vocals of a given string\n");
    char a[] = "This is a sample word";
    char vocals[] = "aeiou";
    printf("String before squeeze: %s\n", a);
    squeeze(a, vocals);
    printf("String after squeeze: %s\n", a);

    return 0;
}

void squeeze(char s1[], char s2[]) {
    int i, j, k; /* Indeces */
    int found;	 /* Variable to check if char is in s2 */
    for (i = k = j = 0; s1[i] != '\0'; i++) {
	/* The idea is to copy each char one by one, and if we find one
	 * in s2, we skip it. Easy*/
	for (k = found = 0; !found && s2[k] != '\0'; k++) {
	    found = (s1[i] == s2[k]);
	}
	/* If the character is not in s2, we copy it. Otherwise, the i index
	 * increments and the character is skipped */
	if (!found) {
	    s1[j++] = s1[i];
	}
    }
    s1[j] = '\0';
}
