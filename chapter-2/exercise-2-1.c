/*
 * Exercise 2-1. Write a program to determine the ranges of char, short, int,
 * and long variables, both signed and unsigned, by printing appropriate values
 * from standard headers and by direct computation. Harder if you compute them:
 * determine the ranges of the various floating-point types.
 * */

#include <limits.h>
#include <stdio.h>

int main() {

    printf("Char range: {%d, %d}\n", CHAR_MIN, CHAR_MAX);
    printf("Short range: {%d, %d}\n", SHRT_MIN, SHRT_MAX);
    printf("Int range: {%d, %d}\n", INT_MIN, INT_MAX);
    printf("Long range: {%ld, %ld}\n", LONG_MIN, LONG_MAX);

    return 0;
}
