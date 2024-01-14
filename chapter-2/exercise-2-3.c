#include <stdio.h>

/*
 * Exercise 2-3. Write a function htoi(s), which converts a string of
 * hexadecimal digits (including an optional 0x or 0X) into its equivalent
 * integer value. The allowable digits are 0 through 9, a through f, and A
 * through F.
 * */

double htoi(char s[]); /* Converts a string of HEX valued number into a decimal
	   number */
int main() {

    /* Both of them sould spit the same number: 2748 */
    char hexnum_withprefix[] = "0xABC";
    char hexnum_withupperprefix[] = "0XABC";
    char hexnum_woprefix[] = "ABC";
    char hexnum_lowercase[] = "abc";

    printf("Hex num with prefix: %s -> %f\n", hexnum_withprefix,
	   htoi(hexnum_withprefix));
    printf("Hex num with uppercase prefix: %s -> %f\n", hexnum_withupperprefix,
	   htoi(hexnum_withupperprefix));
    printf("Hex num without prefix: %s -> %f\n", hexnum_woprefix,
	   htoi(hexnum_woprefix));
    printf("Hex num without prefix in lowercase: %s -> %f\n", hexnum_lowercase,
	   htoi(hexnum_lowercase));
}

double htoi(char s[]) {
    double n; /* Let's assume its a double so it does not overflow so easily */
    int i;

    /* Let's check if 0x or 0X exists */
    if (s[0] == '0') {
	if (s[1] == 'X' || s[1] == 'x') {
	    /* We skip the first two characters*/
	    i = 2;
	} else {
	    i = 0;
	}
    } else {
	i = 0;
    }

    n = 0; /* Set the variable to avoid strange values */
    /* Perform the main loop */
    for (i = i; s[i] != '\0' &&
		((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f') ||
		 (s[i] >= 'A' && s[i] <= 'F'));
	 ++i) {
	int offset;
	if (s[i] >= '0' && s[i] <= '9') {
	    offset = s[i] - '0';
	} else if (s[i] >= 'a' && s[i] <= 'f') {
	    offset = s[i] - 'a' + 10;
	} else if (s[i] >= 'A' && s[i] <= 'F') {
	    offset = s[i] - 'A' + 10;
	}
	n = n * 16 + offset;
	printf("n = %f\n", n);
    }

    return n;
}
