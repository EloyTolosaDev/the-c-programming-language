#include <stdio.h>
#include <limits.h>     /* For INT_MIN variable */
#include <string.h>    /* For strlen() function */

/**
 * Exercise 3-4. In a two's complement number representation, our version of itoa does not 
 * handle the largest negative number, that is, the value of n equal to -(2wordsize-1). Explain why 
 * not. Modify it to print that value correctly, regardless of the machine on which it runs. 
 * 
 * The reason this does not work is because any number equal to the minimum number of its range,
 * converted to negative, is equal to itself. This is because of how two's complement work.
 * 
 * To solve this, you have to check first if the number is equal to the min range of the integer type,
 * and if it is, add it a 1. Then complete the function as desired and, at the end, before reversing
 * the string, youu have to add the 1 we previously subtracted to the first digit of the number.
 **/
 
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
void itoa (int n, char s[]) {
  int i, sign, lowest;
  if (lowest = (n == INT_MIN))
    n++;
    
  if ((sign = n) < 0)			/* record sign */
	n = -n;						/* make n positive */
  i = 0;
  do
	{							/* generate digits in reverse order */
	  s[i++] = n % 10 + '0';	/* get next digit */
	}
  while ((n /= 10) > 0);		/* delete it */
  if (sign < 0)
	s[i++] = '-';
  s[i] = '\0';
  if (lowest)
    s[0]++;   /* Add the 1 we subtracted at the beginning */
  reverse (s);
}

#define MAXLEN 1000

int main () {
  
    char s[MAXLEN];
    int n = INT_MIN;
    
    itoa(n, s);
    
    printf("INT_MIN as a string **fixed**: %s\n", s);

    return 0;
}

