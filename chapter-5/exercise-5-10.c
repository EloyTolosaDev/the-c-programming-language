#include <ctype.h>
#include <math.h> /* for fmod() */
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '1' /* signal that a number was found */
#define NONE '0'

/**
 * Exercise 5-10. Write the program expr, which evaluates a reverse Polish
 * expression from the command line, where each operator or operand is a
 * separate argument.
 * */

int getop(char *s);
void push(double f);
double pop();

#define MAXVAL 100  /* maximum depth of val stack */
int sp = 0;	    /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
	val[sp++] = f;
    else
	printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop() {
    if (sp > 0) {
	return val[--sp];
    } else {
	printf("error: stack empty\n");
	return 0.0;
    }
}

/* getop: get next character or numeric operand */
int getop(char *s) {
    if (s == NULL)
	return NONE;
    return isdigit(*s) ? NUMBER : *s;
}

int main(int argc, char **args) {
    int type;
    double op2;

    /**
     * *args[0] is the name of the program. We need to increment it first to
     * get the actual arguments.
     * */
    /**
     * NOTE: This will not be useful in a local machine.
     * This is only because I'm doing it in this website.
     * But in local, we would only increment it once.
     * */
    while (getop(*args) != NUMBER)
	*args++;

    while ((type = getop(*args)) != EOF) {
	switch (type) {
	case NUMBER:
	    push(atof(*args));
	    break;
	case '+':
	    push(pop() + pop());
	    break;
	case '*':
	    push(pop() * pop());
	    break;
	case '-':
	    op2 = pop();
	    push(pop() - op2);
	    break;
	case '/':
	    op2 = pop();
	    if (op2 != 0.0)
		push(pop() / op2);
	    else
		printf("error: zero divisor\n");
	    break;
	case '%':
	    op2 = pop();
	    /* Check if the numbers are integers */
	    if (op2 >= 0.0)
		push(fmod(pop(), op2));
	    else
		printf("error: zero divisor\n");
	    break;
	case NONE:
	default:
	    printf("Number returned: %.8f\n", pop());
	    return 1;
	}
	*args++;
    }
    return EXIT_SUCCESS;
}
