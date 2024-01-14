#include <stdio.h>

/*
 * Exercise 2-5. Write the function any(s1,s2), which returns the first location
 * in a string s1 where any character from the string s2 occurs, or -1 if s1
 * contains no characters from s2. (The standard library function strpbrk does
 * the same job but returns a pointer to the location.)
 * */

int any(char s1[], char s2[]);
void test(char s1[], char s2[]);

int main() {

    printf("In this program we wrote a function, 'any' that checks if a "
	   "string 's1' contains any character in the string 's2'.\n");
    printf("\n");

    printf("TEST 1: s1 contains a character from s2\n");
    /* Test 1: s1 contains a character from s2 */
    char a[] = "Thermometer";
    char b[] = "eoet";
    test(a, b); /* The value it sould return is 2 */

    printf("TEST 2: s1 does not contain a character from s2\n");
    /* Test 1: s1 contains a character from s2 */
    char c[] = "The brown caterpillar climbs up to the tree";
    char d[] = "xyzq";
    test(c, d); /* The value it sould return is 2 */

    return 0;
}

void test(char s1[], char s2[]) {
    int cvalue;
    cvalue = any(s1, s2);
    if (cvalue >= 0) {
	printf(
	    "The word '%s' contains the character %c in '%s' at position %d\n",
	    s1, s1[cvalue], s2, cvalue);
    } else {
	printf("The word '%s' does not contain any character from '%s'\n", s1,
	       s2);
    }
}

int any(char s1[], char s2[]) {
    int i, k;  /* Indeces */
    int found; /* Variable to check if char is in s2 */
    for (i = k = 0; s1[i] != '\0'; i++) {
	for (k = found = 0; !found && s2[k] != '\0'; k++) {
	    found = (s1[i] == s2[k]);
	}
	/* If we find the word in the string, we return the 'i' index.
	 * Otherwise, we return -1 if we reached the end of the s1 string*/
	if (found) {
	    return i;
	}
    }
    return -1;
}
