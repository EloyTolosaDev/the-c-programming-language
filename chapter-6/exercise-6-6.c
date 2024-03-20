#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct nlist { /* table entry: */ 
struct nlist *next; /* next entry in chain */ 
char *name; /* defined name */ 
char *defn; /* replacement text */ 
};

#define HASHSIZE 101 
static struct nlist *hashtab[HASHSIZE]; /* pointer table */ 

void print_hashtable(struct nlist* hashtable[]) {
	printf("HASHTABLE:\n");
	for (int i = 0; i < HASHSIZE; i++) {
		int count = 0;
		for (struct nlist* node = hashtable[i]; node != NULL; node = node->next) {
			count++;
			printf("%s=%s -> ", node->name, node->defn);
		}
		if (count > 0)
			printf("\n");
	}
}

/* hash: form hash value for string s */ 
unsigned hash(const char *s) { 
	unsigned hashval; 
	for (hashval = 0; *s != '\0'; s++) 
		hashval = *s + 31 * hashval; 
	return hashval % HASHSIZE; 
}

/* lookup: look for s in hashtab */ 
struct nlist *lookup(char *s) { 
	struct nlist *np; 
	for (np = hashtab[hash(s)]; np != NULL; np = np->next) 
		if (strcmp(s, np->name) == 0) 
			return np; /* found */ 
	return NULL; /* not found */ 
} 

/* install: put (name, defn) in hashtab */ 
struct nlist *install(char *name, char *defn) { 
	struct nlist *np; 
	unsigned hashval; 
	if ((np = lookup(name)) == NULL) { /* not found */ 
		np = (struct nlist *) malloc(sizeof(*np)); 
		if (np == NULL || (np->name = strdup(name)) == NULL) 
			return NULL; 
		hashval = hash(name); 
		np->next = hashtab[hashval]; 
		hashtab[hashval] = np; 
	} else /* already there */ 
		free((void *) np->defn); /*free previous defn */ 

	if ((np->defn = strdup(defn)) == NULL) 
		return NULL; 

	return np; 
}

/**
 * Exercise 6-6. Implement a simple version of the #define processor (i.e., no arguments) 
 * suitable for use with C programs, based on the routines of this section. You may also find 
 * getch and ungetch helpful.
 * */

int getword( char *word, int lim ) {

	int c, getch( void );
	void ungetch( int );
	char* w = word;

	/* skip initial whitespaces */
	while( (c = getch()) == ' ');

	/**
	 * Skip comments
	 * */
	if (c == '\"') 
		while ( (c = getch()) != '\"');

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

	while (c != EOF && c != ' ' && c != '.' && c != ',' && c != '\n') {
		*word++ = c;
		c = getch();
	}
	if (c == EOF)
		return EOF;
	if (c == '\n')
		return '\n';

	/* end string with NULL terminator  */
	*word++ = '\0';

	return *w;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch( void ) { return ( bufp > 0 ) ? buf[ --bufp ] : getchar(); }

void ungetch( int c ) {
	if ( bufp >= BUFSIZE )
		printf( "ungetch: too many characters\n" );
	else
		buf[ bufp++ ] = c;
}

#define MAXWORDSIZE BUFSIZE

#define ALLOCSTR malloc(sizeof(char) * MAXWORDSIZE)

int main(int argc, char* argv[]) {

	int c;
	char* word = malloc(sizeof(char) * MAXWORDSIZE);
	while((c = getword(word, MAXWORDSIZE)) != EOF) {
		if (c == '#') {
			if (strcmp(word+1, "define") == 0) {
				char* var = ALLOCSTR;
				getword(var, MAXWORDSIZE);
				
				char* defn = ALLOCSTR;
				getword(defn, MAXWORDSIZE);
	
				printf("[main] found new definition #%s %s %s\n", word+1, var, defn);
				install(var, defn);
			}
		}
	}
	
	print_hashtable(hashtab);

	return 0;
}