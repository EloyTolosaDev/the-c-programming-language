#include <stdio.h>

/**
 * Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of
 * type t.
 * */

#define swap(t, a, b)                                                          \
    {                                                                          \
	t temp = a;                                                            \
	a = b;                                                                 \
	b = temp;                                                              \
    }

int main() {

    int x = 42, y = 21;
    printf("Before swapping: x=%d and y=%d\n", x, y);
    swap(int, x, y);
    printf("After swapping: x=%d and y=%d\n", x, y);

    return 0;
}
