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
		for (struct nlist* node = hashtable[i]; node != NULL; node = node->next) {
			printf("%s=%s -> ", node->name, node->defn);
		}
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
 * Exercise 6-5. Write a function undef that will remove a name and definition from the table 
 * maintained by lookup and install.
 * */

/**
 * Carefully frees all the memory allocated for the node.
 * */
void free_listnode(struct nlist* node) {
	free(node->name);
	free(node->defn);
	node->next = NULL;
	free(node);
}

/**
 * In this case it is not just a trivial case of lookup and add. There's a lot of 
 * chances of collisions in this lookup table, so, In case that we encounter a collision,
 * we need to apply the algorithm to remove an element from a linked list: once we find 
 * the element to remove, make the previous element point to the element next to the one we 
 * must remove. Then, de-allocate the memory of that element.
 * */
void undef(const char* name) {
	struct nlist *n, *pn; /* Node and previous node */
	for (n = hashtab[hash(name)], pn = NULL; n != NULL; pn = n, n=n->next)  {
		if (strcmp(name, n->name) == 0) {
			/* word is in the middle of the list */
			if (pn != NULL) {
				pn->next = n->next;
			} else {
				/* word is at the beginning of the list */ 	
				hashtab[hash(name)] = n->next;
			}
			/* make sure we release all the memory allocated for that node */
			free_listnode(n);
			return;
		}
	}
}

int main(int argc, char* argv[]) {

	/**
	 * Introduce random variables and test if there are collisions
	 * */
	const char* abc = "abcdefghijklmnopq";
	int len = strlen(abc);
	int limit = HASHSIZE;
	for (int i = 0; i < strlen(abc)-1 && limit > 0; i++) {
		for(int j = 0; j < strlen(abc)-1 && limit > 0; j++) {
			char var[] = {*(abc+i), *(abc+j), '\0'};
			install(var, "asdf");
		}
	}

	/**
	 * We're going to remove the variable 'gp' which is in the middle of a
	 * variable list, and 'mo' wich is at the beginning of a list
	 * and see if it removed okay using grep after running the program.
	 */
	undef("gp");
	undef("mo");
	print_hashtable(hashtab);

	/**
	 * To test the program, run
	 *	./main | grep gp
	 * And see that no occurrence is found. You can remove grep and see the 
	 * list of nodes and see how the hash table is constructed.
	 
	 * You can play and see how the distribution changes when you change the hashtable
	 * size.
	 * */
		
	return 0;
}
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
		for (struct nlist* node = hashtable[i]; node != NULL; node = node->next) {
			printf("%s=%s -> ", node->name, node->defn);
		}
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
 * Exercise 6-5. Write a function undef that will remove a name and definition from the table 
 * maintained by lookup and install.
 * */

/**
 * Carefully frees all the memory allocated for the node.
 * */
void free_listnode(struct nlist* node) {
	free(node->name);
	free(node->defn);
	node->next = NULL;
	free(node);
}

/**
 * In this case it is not just a trivial case of lookup and add. There's a lot of 
 * chances of collisions in this lookup table, so, In case that we encounter a collision,
 * we need to apply the algorithm to remove an element from a linked list: once we find 
 * the element to remove, make the previous element point to the element next to the one we 
 * must remove. Then, de-allocate the memory of that element.
 * */
void undef(const char* name) {
	struct nlist *n, *pn; /* Node and previous node */
	for (n = hashtab[hash(name)], pn = NULL; n != NULL; pn = n, n=n->next)  {
		if (strcmp(name, n->name) == 0) {
			/* word is in the middle of the list */
			if (pn != NULL) {
				pn->next = n->next;
			} else {
				/* word is at the beginning of the list */ 	
				hashtab[hash(name)] = n->next;
			}
			/* make sure we release all the memory allocated for that node */
			free_listnode(n);
			return;
		}
	}
}

int main(int argc, char* argv[]) {

	/**
	 * Introduce random variables and test if there are collisions
	 * */
	const char* abc = "abcdefghijklmnopq";
	int len = strlen(abc);
	int limit = HASHSIZE;
	for (int i = 0; i < strlen(abc)-1 && limit > 0; i++) {
		for(int j = 0; j < strlen(abc)-1 && limit > 0; j++) {
			char var[] = {*(abc+i), *(abc+j), '\0'};
			install(var, "asdf");
		}
	}

	/**
	 * We're going to remove the variable 'gp' which is in the middle of a
	 * variable list, and 'mo' wich is at the beginning of a list
	 * and see if it removed okay using grep after running the program.
	 */
	undef("gp");
	undef("mo");
	print_hashtable(hashtab);

	/**
	 * To test the program, run
	 *	./main | grep gp
	 * And see that no occurrence is found. You can remove grep and see the 
	 * list of nodes and see how the hash table is constructed.
	 
	 * You can play and see how the distribution changes when you change the hashtable
	 * size.
	 * */
		
	return 0;
}
