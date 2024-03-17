#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Exercise 6-2. Write a program that reads a C program and prints in
 * alphabetical order each group of variable names that are identical in the
 * first 6 characters, but different somewhere thereafter. Don't count words
 * within strings and comments. Make 6 a parameter that can be set from the
 * command line.
 */

/**
 * To make this program, we will use the keyword list provided in the following
 * github repository:
 * https://github.com/Elyasin/K-and-R-solutions/blob/master/Exercise%206-2/var_group.c
 *
 * The key of this exercise is creating a tree, as the section 1 of the chapter
 * 6, and insert the words in alphabetical order, keeping in mind the X
 * character prefix coincidence.
 */

char *keywords[] = {
		"auto",     "break",  "case",    "char",   "const",    "continue",
		"default",  "do",     "double",  "else",   "enum",     "extern",
		"float",    "for",    "goto",    "if",     "int",      "long",
		"register", "return", "short",   "signed", "sizeof",   "static",
		"struct",   "switch", "typedef", "union",  "unsigned", "void",
		"volatile", "while" };

#define NKEYWORDS sizeof(keywords)/sizeof(keywords[0])

#define DEFAULT_PREFIXLEN 6

/**
 * tnode functions and declarations
 */

struct tnode {
	char *word;
	int id;
	struct tnode *left, *right;
};

/* returns a pointer to a memory space allocated for a tnode struct */
struct tnode* talloc() {
	return (struct tnode*) malloc(sizeof(struct tnode));
}

// adds a word to the tree
struct tnode* add_word(struct tnode* root, char* word, int prefixlen) {
	static int id = 1;
	if (root == NULL){
		root = talloc();
		root->word = strdup(word);
		root->id = id++;
		root->left = NULL;
		root->right = NULL;
		//printf("[add_word] node added (%s, %d)\n", root->word, root->id);
	} else {
		int cmp = strncmp(root->word, word, prefixlen);
		if ( cmp < 0) {
			root->right = add_word(root->right, word, prefixlen);	
		} else if ( cmp > 0 ) {
			root->left = add_word(root->left, word, prefixlen);	
		} else {
			//printf("[add_word] %s already exists in the tree\n", word);
		}
	}
	return root;
}

/**
 * print all the words that have n characters in common between them.
 */
void print_tree(struct tnode* root) {
	printf("node[%d]=%s\n", root->id, root->word);
	if (root->left != NULL)
		print_tree(root->left);
	if (root->right != NULL)
		print_tree(root->right);
}

/**
 * getword, getch and ungetch
 */

int getword(char *word, int lim) {

	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()));

	if (c != EOF)
		*w++ = c;

	/**
	 * In this case we will not return string constants as this
	 * program only wants to handle variable names.
	 *
	 * So, we wil skip string constants
	 * */
	if (c == '\"') 
		while ( (c = getch()) != '\"');

	/**
	 * Also, in this case we will not take into account the limit 
	 * so we skip the entirety of a comment, be it single line or
	 * multi-line.
	 * */
	if (c == '/') {
		c = getch();
		// Single line comments
		if (c == '/') {
			while ( (c = getch()) != '\n');
			
		} else if (c == '*') {
			int pc = c;
			c = getch();
			while (c != '/' || pc != '*')
				pc = c, c = getch();
		} else {
			ungetch(c);
			*w = '\0';
			return '/';
		}
	}
	// Consume preprocessor control lines
	if (c == '#') {
		// Simple assumption: starts with '#' and ends with '\n'
		for (; --lim > 0; w++)
			if ((*w = getch()) == '\n')
				break;
	}
	if (!isalpha(c) && c != '_') {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++) {
		if (!isalnum(*w = getch()) && *w != '_') {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* binary search over keywords */
int iskeyword(char* word) {
	int i, j, mid, cmp;
	for (i = 0, j = NKEYWORDS-1, mid = (i+j)/2; i <= j; mid = i + (j-i)/2) {
		cmp = strcmp(word, keywords[mid]);
		if (cmp < 0)
			j = mid-1;
		else if (cmp > 0)
			i = mid+1;
		else
			return 1;
	}
	return 0;
}

#define MAXWORDLEN BUFSIZE

int main(int argc, char *argv[]) {

	// set prefix length
	int prefixlen = DEFAULT_PREFIXLEN;
	if ( argc > 1 ) {
		if ( (prefixlen = atoi(argv[1])) > 0) {
			printf("Unable to set prefix length to 0 or less."
				" Setting prefix length to default (%d)\n", DEFAULT_PREFIXLEN);
			prefixlen = DEFAULT_PREFIXLEN;
		} 
	}

	struct tnode* root = NULL;
	char *word = malloc(sizeof(char) * MAXWORDLEN);
	while (getword(word, MAXWORDLEN) != EOF) {
		/* check if the given word starts with an alpha character */
		if (isalpha(*word) && !iskeyword(word))
			root = add_word(root, word, prefixlen);
	}

	print_tree(root);

	return 0;
}
