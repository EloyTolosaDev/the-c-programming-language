#include <stdio.h>

/**
 * Exercise 4-8. Suppose that there will never be more than one character of
 * pushback. Modify getch and ungetch accordingly.
 * */

int getch();
void ungetch(int c);

int main() {

    printf("Write a character to read into the buffer: ");
    int c = getch();
    printf("\nThe character you wrote into the buffer was: %c\n", EOF);

    return 0;
}

/**
 * getch and ungetch section
 * */

int cb;

int getch() {
    int c;
    if (!cb) {
	c = getchar();
    } else {
	c = cb;
	cb = 0;
    }
    return c;
}

void ungetch(int c) {
    if (!cb)
	cb = c;
}
