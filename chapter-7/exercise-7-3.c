#include <stdarg.h>
#include <stdio.h>

/**
 * Exercise 7-3. Revise minprintf to handle more of the other facilities of
 * printf.
 * */

void minprintf(char *fmt, ...) {

	/* variable list type */
	va_list vap;

	/**
   * you have to pass fmt so that va_start knows which was the last known
   * variable before the variaditic argument list.
   *
   * Now 'vap' points to the first unnamed argument (right after fmt).
   * */
	va_start(vap, fmt);

	/**
   * Variables needed to format
   * */
	int int_arg, char_arg, hex_arg;
	double double_arg;
	char *string_var;
	void *ptr_var;

	/**
   * Now we have to iterate the fmt string to know which type of argument
   * to print or parse correctly.
   * */

	/* Store a copy of fmt so we do not lose fmt value after the call */
	char *f = fmt;
	while (*f != '\0') {
		if (*f++ != '%')
			putchar(*f);
		else {
			switch (*f) {
				case '%':
					break;
				/* Add on 1: format ints with 'i' or 'd' */
				case 'd':
				case 'i':
					int_arg = va_arg(vap, int);
					printf("%d", int_arg);
					break;

				case 'f':
					double_arg = va_arg(vap, double);
					printf("%f", double_arg);
					break;

				/* Add on 2: format chars */
				case 'c':
					char_arg = va_arg(vap, int);
					putchar(char_arg);
					break;

				case 's':
					string_var = va_arg(vap, char *);
					while (*string_var)
						putchar(*string_var++);
					break;

				/* Add on 3: format hex numbers */
				case 'x':
				case 'X':
					hex_arg = va_arg(vap, int);
					printf("%x", hex_arg);
					break;

				/* Add on 4: format pointers */
				case 'p':
					ptr_var = va_arg(vap, void *);
					printf("%p", ptr_var);
					break;
				default:
					// printf("[minprintf] putting char %d\n", *f);
					break;
			}
		}
	}

	/* cleanup when done */
	va_end(vap);
}

int main(int argc, char *argv[]) {
	minprintf("%d = %i - %i\n", 4, 2, 2);
	minprintf("%f\n", 0.2563);
	minprintf("%c\n", 'A');
	minprintf("%s\n", "Hello world!");
	minprintf("%x is 255 in HEX!\n", 255);
	minprintf("%p is the pointer of a string\n", "Hello world");
}
