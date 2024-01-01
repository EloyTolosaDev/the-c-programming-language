#include <stdio.h>

int main() {
    // write a program to count blanks, tabs and newlines
    int b, t, nl;
    b = t = nl = 0;

    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            ++t;
        } else if (c == ' ') {
            ++b;
        } else if (c == '\n') {
            ++nl;
        }
    }

    printf("Number of blanks: %d", b);
    printf("Number of tabs: %d", t);
    printf("Number of newlines: %d", nl);

    return 0;
}
