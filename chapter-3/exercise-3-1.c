#include <stdio.h>
#include <time.h>

/*
 * Exercise 3-1. Out binary search makes two tests inside the loop where one
 * would only suffice (at the price of more tests outside). Write a version with
 * only one test inside and measure the difference in runtime.
 * */

/*
 * We're going to declare two binsearch algorithms so we can test the runtime
 * difference
 * */
int binsearch_classic(int x, int v[], int n);
int binsearch_new(int x, int v[], int n);

int main() {

    int maxlen = 1000000;
    /*
     * Create a long enough array to check differences in runtime.
     * */
    int v[maxlen];
    for (int i = 0; i < maxlen; i++) {
	printf("v[%d]=%d\n", i, i);
	v[i] = i;
    }

    printf("Performing binsearch_classic()...\n");
    clock_t begin = clock();
    binsearch_classic(3, v, 20);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("binsearch_classic() found element 3 in %fs\n", time_spent);

    printf("Performing binsearch_new()...\n");
    begin = clock();
    binsearch_new(3, v, 20);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("binsearch_new() found element 3 in %fs\n", time_spent);

    return 0;
}

int binsearch_new(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
	mid = (low + high) / 2;
	if (x < v[mid]) {
	    high = mid - 1;
	} else {
	    low = mid + 1;
	}
    }
    if (v[mid] != x) {
	return -1;
    }

    return mid;
}

int binsearch_classic(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
	mid = (low + high) / 2;
	if (x < v[mid]) {
	    high = mid + 1;
	} else if (x > v[mid]) {
	    low = mid + 1;
	} else {
	    /* Element found */
	    return mid;
	}
    }
    /* return -1 if the element was not found in v */
    return -1;
}
