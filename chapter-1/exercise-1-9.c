#include <stdio.h>

int main() {
    /*
     * Write a program to copy its input to its output, replacing each string of
     * one or more blanks by a single blank
     * */
    int c, pc; // c is current and pc is previous character
    while ((c = getchar()) != EOF) {
        if (c == ' ' && pc == ' ') {
            continue;
        }
        printf("%c", c);
        pc = c;
    }
}
