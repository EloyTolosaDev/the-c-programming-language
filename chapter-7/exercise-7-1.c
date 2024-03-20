#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Exercise 7-1. Write a program that converts upper case to lower or lower case to upper, 
 * depending on the name it is invoked with, as found in argv[0].
 * */

int main(int argc, char* argv[]) {

	int (*f)(int c);
	if (strcmp(argv[1], "lower") == 0) {
		f = tolower;
	} else if (strcmp(argv[1], "upper")) {
		f = toupper;	
	}

	int c;
	while((c = getchar()) != EOF)
		printf("%c", f(c));
	
	return 0;
}