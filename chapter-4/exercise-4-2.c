#include <stdio.h>
#include <ctype.h> /* for isdigit() */

/**
 * Exercise 4-2. Extend atof to handle scientific notation of the form 
 *  123.45e-6 
 * where a floating-point number may be followed by e or E and an optionally signed exponent. 
 * */

/* atof: convert string s to double */ 
double atof(char s[]) { 
    double val, power; 
    int i, sign; 
    
    for (i = 0; isspace(s[i]); i++);     /* skip white space */ 

    sign = (s[i] == '-') ? -1 : 1; 
    if (s[i] == '+' || s[i] == '-') 
        i++;
        
    for (val = 0.0; isdigit(s[i]); i++) 
        val = 10.0 * val + (s[i] - '0'); 
    
    if (s[i] == '.') 
        i++; 
    
    for (power = 1.0; isdigit(s[i]); i++) { 
        val = 10.0 * val + (s[i] - '0'); 
        power *= 10; 
    }
    
    printf("Value before exponent: %f.\n", val);
    
    /** If it's not digit, could be end of string or the 'e'
     * character.
     * If it's an 'e', then get the exponent and add the power
     * in accordance: if e>=0, then power decreases
     * because we are **dividing** by the power, and if e<0
     * then power increases.
     * */
    if (s[i] == 'e') {
        int positive = (s[++i] == '-') ? 0 : 1;
        int exponent = s[++i] - '0';
        for (int j = 0; j < exponent+2; j++) {
            if (positive)
                power /= 10;
            else
                power *= 10;
        }
    }
     
    return sign * val / power; 
}


int main() {
    
    char number[] = "123.45e-6";
    printf("The double representation of %s is %.10f.\n", number, atof(number));

    return 0;
}



