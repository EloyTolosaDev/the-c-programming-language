#include <stdio.h>

#define NEWLINE '\n'
#define TAB '\t'
#define ESCAPE '\\'

#define STRLEN 1000

/* Sets visible tabs and newlines to invisible characters */
void setInvisible(char s[], char t[]);
/* Sets invisible tabs and newlines to visible characters */
void setVisible(char s[], char t[]);

int main(int argc, char *argv[]) {
    char s[] = "The cat \t and the dog \n jumped to the roof \n";
    char t[STRLEN], tt[STRLEN];
    printf("This is the string we want to transform:\n\t%s\n", s);
    setVisible(s, t);
    printf("The string after transforming is:\n\t%s\n", t);
    setInvisible(t, tt);
    printf("The string, after re-transforming is:\n\t%s\n", tt);
    printf("If the strings are equal after re-transforming, the program is "
	   "fine\n");
    printf("Bye\n");
    return 0;
}

void setInvisible(char s[], char t[]) {
    int i, j;
    for (i = j = 0; s[i] != '\0'; i++, j++) {
	switch (s[i]) {
	case ESCAPE:
	    /* If we find a escape character, we need to see if the next
	     * character is either a n or a t to substitute it
	     * */
	    if (s[i + 1] == 'n') {
		t[j] = '\n';
	    }
	    if (s[i + 1] == 't') {
		t[j] = '\t';
	    }
	    i++;
	    break;
	default:
	    t[j] = s[i];
	    /* Even though it is not necessary, as the book says, it is very
	     * responsible to put a break in every case statement. Just a little
	     * "defensive programming"
	     * */
	    break;
	}
    }
    /* Correctly finish the string */
    t[j] = '\0';
}

void setVisible(char s[], char t[]) {
    int i, j;
    for (i = j = 0; s[i] != '\0'; i++, j++) {
	switch (s[i]) {
	case TAB:
	    t[j] = '\\';
	    t[++j] = 't';
	    break;
	case NEWLINE:
	    t[j] = '\\';
	    t[++j] = 'n';
	    break;
	default:
	    t[j] = s[i];
	    /* Even though it is not necessary, as the book says, it is very
	     * responsible to put a break in every case statement. Just a little
	     * "defensive programming"
	     * */
	    break;
	}
    }
    /* Correctly finish the string */
    t[j] = '\0';
}
