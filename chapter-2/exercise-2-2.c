#include <stdio.h>

/*
 * Exercise 2-2. Write a loop equivalent to the for loop above without using &&
 * or ||.
 * */

/*
 * This is easy to solve. We must know that a logical operation
 * returns 0 if false and 1 if true. If we do not want to use && or ||
 * we can use multiplication and addition to do the same.
 *
 * Here's why:
 * An 'and' statement returns 1 if and only if all of its inner
 *  statements are 1. If only one statement is false, it will make
 *  the whole statement false. If instead, we use multiplication,
 *  we multiply 1 by 1 for each true statement. If all true statements
 *  are true, then 1 will be returned, thus being true. And if any
 *  statement returns false, 0 will be returned, because of multiplication
 *  by 0.
 *
 * Similarly happens with the 'or' statement:
 *  The 'or' statement returns 1 if only one of their sub expressions
 *  returns 1. If we compute the sum of multiple sub-expressions,
 *  given that only one returned true (1), adding 1 to the whole
 *  expression would return 1 in the end.
 *
 * We're gonna test two loops and see how the emulation works perfectly.
 *
 * */

#define LIM 20 /* 20 chars lim for loop*/

int main() {

    int i, j;
    int c, d;

    /* Loop to read chars from stdin using conventional && */
    printf("Please, enter text:\n\t");

    printf("Writing a piece of text using conventional && operator: \n");
    for (i = 0; i < LIM - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
	printf("%c", c);
    printf("\n");

    printf("Writing a piece of text using multiplication: \n");
    /* Loop to read chars from stdin using conventional multiplication */
    for (j = 0; (j < LIM - 1) * ((d = getchar()) != '\n') * (d != EOF); ++j)
	printf("%c", d);
    printf("\n");

    return 0;
}
