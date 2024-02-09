#include <stdio.h>
#include <string.h> /* For strlen() */

/**
 * Exercise 4-1. Write the function strindex(s,t) which returns the position of the rightmost
 * occurrence of t in s, or -1 if there is none.
 * */
 
 #define MAXLEN 1000
 
/** We start with this strindex definition from the book's page 
 * 64, but we do it at the reverse: we start from the end, and we
 * search from end to beginning.
 * */ 
int strindex(char s[], char t[]) { 
    int i, j, k; 
    for (i = strlen(s)-1; s[i] != '\0'; i--) { 
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
            ; 
        if (k > 0 && t[k] == '\0') 
            return i; 
    } 
    return -1; 
}

int main() {
    
    /* First occurrence from the right is at index 11*/
    char s[] = "caterpillarpillar";
    char t[] = "pill";
    
    printf("The first occurrence of %s inside %s, starting from the right is %d.\n", t, s, strindex(s, t));

    return 0;
}

