#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
 * LOONG COMMENT
 */

#define BUFSIZE 100
#define MAXWORD 1000

char buf[BUFSIZE];
int bufp = 0;

char *keytab[] = {
	"#define",
	"#include",
	"*/",
	"/*",
	"auto",
	"break",
	"case",
	"char",
	"const",
	"continue",
	"default",
	"do",
	"double",
	"else",
	"enum",
	"extern",
	"float",
	"for",
	"goto",
	"if",
	"int",
	"long",
	"register",
	"return",
	"short",
	"signed",
	"sizeof",
	"static",
	"struct",
	"switch",
	"typedef",
	"union",
	"unsigned",
	"void",
	"volatile",
	"while",
};

char *types[] = {
	"char",
	"double",
	"float",
	"int",
	"long",
	"short",
	"unsigned",
};

struct tnode {
	char *word;
	struct tnode *left;
	struct tnode *inner;
	struct tnode *right;
};

#define NKEYS (sizeof keytab / sizeof(keytab[0]))
#define NTYPES (sizeof types / sizeof(types[0]))

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *my_strdup(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s)+1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

char *my_strndup(char *s, int c)
{
	char *p;
	p = (char *) malloc(strlen(s)+1);
	if (p != NULL)
		strncpy(p, s, c);
	return p;
}

struct tnode *addtree_inner(struct tnode *p, char *w)
{
	int cond;
	if (p == NULL) {
		p = talloc();
		p->word = my_strdup(w);
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
	} else if (cond < 0) {
		p->left = addtree_inner(p->left, w);
	} else {
		p->right = addtree_inner(p->right, w);
	}

	return p;
}

struct tnode *addtree_outer(struct tnode *p, char *w, int c)
{
	int cond;
	if (p == NULL) {
		p = talloc();
		p->word = my_strndup(w, c);
		p->inner = addtree_inner(p->inner, w);
		p->left = p->right = NULL;
	} else if ((cond = strncmp(w, p->word, c)) == 0) {
		p->inner = addtree_inner(p->inner, w);
	} else if (cond < 0) {
		p->left = addtree_outer(p->left, w, c);
	} else {
		p->right = addtree_outer(p->right, w, c);
	}

	return p;
}

void treeprint_inner(struct tnode *p)
{
	if (p) {
		treeprint_inner(p->left);
		printf("%s\n", p->word);
		treeprint_inner(p->right);
	}
}

void treeprint(struct tnode *p)
{
	if (p) {
		treeprint(p->left);
		printf("tree of %s\n", p->word);
		treeprint_inner(p->inner);
		printf("\n");
		treeprint(p->right);
	}
}

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("too many characters in ungetch buf\n");
	else
		buf[bufp++] = c;
}

int getword(char *word, int lim)
{
	int c;
	char *w = word;
	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c) && c != '#' && c != '/' && c != '*') {
		*w++ = '\0';
		return c;
	}

	if (c == '/') 
		if ((c = getch()) == '*') {
			*w++ = c;
			*w = '\0';
			return word[0];
		} else {
			*w = '\0';
			ungetch(c);
			return c;
		}

	if (c == '*') 
		if ((c = getch()) == '/') {
			*w++ = c;
			*w = '\0';
			return word[0];
		} else {
			*w = '\0';
			ungetch(c);
			return c;
		}

	for (; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

int binsearch(char *word, char *tab[], int n)
{
	int cond;
	int low, mid, high;

	low = 0;
	high = n-1;
	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid])) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int istype(char *word)
{
	return (binsearch(word, types, NTYPES) >= 0);
}

int isvar(char word[][MAXWORD], int i, int lim)
{
	int x = 0;
	while (isalnum(word[i][x]))
		x++;
	if (word[i][x] != '\0')
		return 0;
	return istype(word[(i+2)%3]) && word[(i+1)%3][0] != '(';
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("invalid no. of args\n");
		return 1;
	}

	int i = 0;
	int n;
	int c = atoi(argv[1]);
	char word[3][MAXWORD] = {"", "", ""};
	int skip = 0;
	struct tnode *root = NULL;

	while (getword(word[i], MAXWORD) != EOF) {
		if (word[i][0] == '"' || (word[i][0] == '/' && (n = binsearch(word[i], keytab, NKEYS)) >= 0))
			skip = 1;
		if (word[i][0] == '"' || (word[i][0] == '*' && (n = binsearch(word[i], keytab, NKEYS)) >= 0))
			skip = 0;
		if (skip)
			continue;

		if (isvar(word, (i+2)%3, MAXWORD))
			root = addtree_outer(root, word[(i+2)%3], c);
		i++;
		i %= 3;
	}

	treeprint(root);

	return 0;
}
