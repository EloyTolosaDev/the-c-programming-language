#include <stdio.h>
#include <string.h>
#include <limits.h>

/**
 * Exercise 3-6. Write a version of itoa that accepts three arguments instead of two. The third 
 * argument is a minimum field width; the converted number must be padded with blanks on the 
 * left if necessary to make it wide enough.
 * */
 
#define MAXLEN 1000

/* NOTE: This function is in the book's page 59. */
/* reverse: reverse string s in place */ 
void reverse(char s[]) { 
    int c, i, j; 
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) { 
        c = s[i]; 
        s[i] = s[j]; 
        s[j] = c; 
    } 
} 
 
/* itoa: convert n to characters in s */
void itoa (int n, char s[], int minwidth) {
    int i, sign, lowest;
    
    /** If n == INT_MIN, we add a 1 so we can work on it with the normal
     * algorithm, and at the end add the 1 again to the LSB.
     * */
    if (lowest = (n == INT_MIN))
        n++;
    
    if ((sign = n) < 0)			/* record sign */
        n = -n;                 /* make n positive */
    
    i = 0;
    do {							/* generate digits in reverse order */
      s[i++] = n % 10 + '0';	/* get next digit */
    } while ((n /= 10) > 0);		/* delete it */
    
    /* Add the sign if negative */
    if (sign < 0)
        s[i++] = '-';
    
    /* Add the 1 we subtracted at the beginning */
    if (lowest)
        s[0]++;
    
    /** Check if the number length is at least minwidth.
     * If not, we have to add spaces at the end, before
     * reversing the string.
     * */
    if (i < minwidth-1) {
        while (i < minwidth)
            s[i++] = ' ';
    }
    
    s[i] = '\0';
    reverse(s);
}

int main()
{
    char s[MAXLEN];
    int n = 42;
    
    /* We'll make the number 5 characters long */
    itoa(n, s, 5);
    
    printf("Now we print %s and we can see that strlen(n)=%lu\n", s, strlen(s));

    return 0;
}



