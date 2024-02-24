#include <math.h> /* for fmod() */
#include <stdio.h>

/**
 * Exercise 4-4. Add the commands to print the top elements of the stack without
 * popping, to duplicate it, and to swap the top two elements. Add a command to
 * clear the stack.
 * */

#include <stdlib.h> /* for atof() */

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main() {
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {
	switch (type) {
	case NUMBER:
	    push(atof(s));
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
	case '\n':
	    printf("\t%.8g\n", pop());
	    break;
	default:
	    printf("error: unknown command %s\n", s);
	    break;
	}
    }
    return 0;
}

#define MAXVAL 100 /* maximum depth of val stack */

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
double pop(void) {
    if (sp > 0) {
	return val[--sp];
    } else {
	printf("error: stack empty\n");
	return 0.0;
    }
}

/**
 * Prints the top n integers of the stack **without popping them**
 * */
void top(int n) {
    for (int i = sp - 1; i < sp - 1 - n; i++) {
	printf("%f\n", val[i]);
    }
}

/**
 * passes an initialized int[] as a paramter and copies
 * the contents of the stack into it.
 * */
void duplicate(int dup[]) {
    for (int i = 0; i < sp; i++) {
	dup[i] = val[i];
    }
}

/**
 * Swaps the top two elements.
 * */
void swap_top() {
    int t = val[sp - 2];
    val[sp - 2] = val[sp - 1];
    val[sp - 1] = t;
}

/**
 * Clears the stack
 * */
void clear_stack() { sp = 0; }

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[]) {
    int i, c;
    /* skip whitespaces and tabs */
    while ((s[0] = c = getch()) == ' ' || c == '\t')
	;

    i = 0;
    if (isdigit(c)) /* collect integer part */
	while (isdigit(s[++i] = c = getch()))
	    ;

    if (c == '.') /* collect fraction part */
	while (isdigit(s[++i] = c = getch()))
	    ;

    s[i] = '\0';
    if (c != EOF)
	ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;	   /* next free position in buf */

/* get a (possibly pushed-back) character */
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

/* push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
	printf("ungetch: too many characters\n");
    else
	buf[bufp++] = c;
}
