#include <stdio.h>
#include <string.h>

/**
 * Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a base b
 * character representation in the string s. In particular, itob(n,s,16) formats s as a 
 * hexadecimal integer in s. 
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

/**
 * To change any number to any base, we will use the continuous
 * division method.
 * We will divide the number by the base..
 * We will take the quotient of every division to divide the number again.
 * We divide until the quotient is 0.
 * 
 * The solution is the remainders of each division in reversed order.
 * We will use the reverse() function used in the previous exercise.
 * */
void itob(int n, char s[], int b) {
    printf("***** BASE %d *******\n", b);
    int i;
    int quotient, rest;
    int number = n;
    for (i = 0; quotient = number/b, number > 0; i++) {
        rest = number-quotient*b;
        /* Handle >10 bases (like Hex) up until base 16 */
        if (b > 10 && rest >= 10)
            s[i] = 'A' + rest-10;
        else 
            s[i] = '0'+rest;
        

        number = quotient;
    }
    s[i] = '\0';    /* End the string */
    reverse(s);
}


int main()
{
    int n = 255;
    char s[MAXLEN];
    /* Bases to transform: binary, octal, decimal and hex */
    int bases[] = {2, 8, 10, 16};
    
    for (int i = 0; i < 4; i++) {
        itob(n, s, bases[i]);
        printf("%d in base %d = %s\n", n, bases[i], s);
    }

    return 0;
}




