#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Exercise 6-4. Write a program that prints the distinct words in its input
 * sorted into decreasing order of frequency of occurrence. Precede each word by
 * its count.
 * */

/**
 * This exercise is the same as 6-2. You create a tree with the nodes being
 * words and comparing them every time you insert them into the tree. This time,
 * when you see a repeated word, you increase an 'occurrence' counter.
 *
 * After this, we have to create a method that reads a tree and inserts it into
 * a list of words, and then order them using a quicksort variant.
 * */

/**
 * To run this program you have "lorem-ipsum-example" file in the chapter-6 folder, 
 * which you will use as stdin to the program like this:
 *  cat lorem-ipsum-example | ./<program>
 * */

/**
 * TREE METHODS
 * */

struct tnode {
  char *word;
  int id, times;
  struct tnode *left, *right;
};

/* returns a pointer to a memory space allocated for a tnode struct */
struct tnode *talloc() {
  return (struct tnode *)malloc( sizeof( struct tnode ) );
}

int tnode_cmp( struct tnode *a, struct tnode *b ) {
  return a->times - b->times;
}

void tnode_swap( struct tnode *a, struct tnode *b ) {
  struct tnode *aux = talloc();
  *aux = *a;
  *a = *b;
  *b = *aux;
}

// adds a word to the tree
struct tnode *add_word( struct tnode *root, char *word ) {
  static int id = 0;
  if ( root == NULL ) {
    root = talloc();
    root->word = strdup( word );
    root->times = 1;
    root->id = id++;
    root->left = NULL;
    root->right = NULL;
  } else {
    int cmp = strcmp( root->word, word );
    if ( cmp < 0 ) {
      root->right = add_word( root->right, word );
    } else if ( cmp > 0 ) {
      root->left = add_word( root->left, word );
    } else {
      /* increase the counter when we find the same word */
      root->times++;
    }
  }
  return root;
}

/*
 * In-order tree traversal putting the tnode pointers into an array
 * to sort them after
 * */
#define MAXTREELENGTH 1000

void tree_to_list( struct tnode *root, struct tnode *tnode_list[] ) {
  /* insert them in the order of their ids */
  tnode_list[ root->id - 1 ] = root;
  if ( root->left != NULL )
    tree_to_list( root->left, tnode_list );
  if ( root->right != NULL )
    tree_to_list( root->right, tnode_list );
}

void print_tree( struct tnode *root ) {
  printf( "node[%d]=%s (%d times)\n", root->id, root->word, root->times );
  if ( root->left != NULL )
    print_tree( root->left );
  if ( root->right != NULL )
    print_tree( root->right );
}

/**
 * GETWORD, GETCH and UNGETCH
 * */

int getword( char *word, int lim ) {

  int c, getch( void );
  void ungetch( int );
  char* w = word;

  /* skip initial whitespaces */
  while( (c = getch()) == ' ');

  while (c != EOF && c != ' ' && c != '.' && c != ',' && c != '\n') {
    *word++ = c;
    c = getch();
  }
  if (c == EOF)
    return EOF;

  /* end string with NULL terminator  */
  *word++ = '\0';

  return *w;
}

#define BUFSIZE 100

char buf[ BUFSIZE ];
int bufp = 0;

int getch( void ) { return ( bufp > 0 ) ? buf[ --bufp ] : getchar(); }

void ungetch( int c ) {
  if ( bufp >= BUFSIZE )
    printf( "ungetch: too many characters\n" );
  else
    buf[ bufp++ ] = c;
}

#define MAXWORDLEN BUFSIZE

/**
 * QUICKSORT implementation ()
 * */

int partition( struct tnode *words[], int low, int high ) {
  int pivot = high;
  int i = low - 1;

  for ( int j = low; j < high; j++ ) {

    if ( tnode_cmp( words[ j ], words[ pivot ] ) < 0 ) {
      i++;
      tnode_swap( words[ i ], words[ j ] );
    }

  }
  tnode_swap( words[ i+1 ], words[ high ] );
  return i+1;
}

void quicksort( struct tnode *words[], int low, int high ) {
  /* error case to avoid repetitive recursive calls */
  if (low  > high)
    return;

  int p = partition( words, low, high );

  quicksort( words, low, p - 1 );
  quicksort( words, p + 1, high );
}

int main( int argc, char *argv[] ) {

  struct tnode *root = NULL;
  char *word = malloc( sizeof( char ) * MAXWORDLEN );
  while ( getword( word, MAXWORDLEN ) != EOF )
    root = add_word( root, word );


  struct tnode *tnode_list[ MAXTREELENGTH ];
  tree_to_list( root, tnode_list );

  /**
   * TO calculate the list length, we have to iterate it until
   * we find a null
   * */ 
  int tnode_list_len = 0;
  while (tnode_list[tnode_list_len] != NULL)
    tnode_list_len++;

  // printf("tnode list is %d nodes long!", tnode_list_len);
  quicksort( tnode_list, 0, tnode_list_len - 1);


  /* print the list until the first null */
  struct tnode *node = NULL;
  for ( int i = 0; ( node = tnode_list[ i ] ) != NULL; i++ )
    printf( "node[%d]=%s (%d times)\n", node->id, node->word, node->times );

  return 0;
}
