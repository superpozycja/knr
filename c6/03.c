#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 100
#define MAXWORD 1000

char buf[BUFSIZE];
int bufp = 0;

struct lnode {
	int val;
	struct lnode *next;
};

struct tnode {
	char *word;
	struct lnode *llist;
	struct tnode *left;
	struct tnode *right;
};

struct lnode *lalloc(void)
{
	return (struct lnode *) malloc(sizeof(struct lnode));
}

void addlist(struct lnode *p, int n)
{
	if (!p) {
		p = lalloc();
		p->val = n;
		p->next = NULL;
	}
	while (p->next) {
		if (p->val == n)
			return;
		p = p->next;
	}
	p->next = lalloc();
	p->next->val = n;
	p->next->next = NULL;
}

void listprint(struct lnode *p)
{
	while (p) {
		printf("%d ", p->val);
		p = p->next;
	}
}

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

struct tnode *addtree(struct tnode *p, char *w, int val)
{
	int cond;
	if (p == NULL) {
		p = talloc();
		p->llist = lalloc();
		p->llist->val = val;
		p->word = my_strdup(w);
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		addlist(p->llist, val);
	} else if (cond < 0) {
		p->left = addtree(p->left, w, val);
	} else {
		p->right = addtree(p->right, w, val);
	}

	return p;
}

void treeprint(struct tnode *p)
{
	if (p) {
		treeprint(p->left);
		listprint(p->llist);
		printf("%s\n", p->word);
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
	while (isspace(c = getch()) && c != '\n')
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

int main()
{
	int i = 0;
	int n;
	int lineno = 1;
	char *word;
	struct tnode *root = NULL;

	while (getword(word, MAXWORD) != EOF) {
		root = addtree(root, word, lineno);
		if (word[0] == '\n')
			lineno++;
	}

	treeprint(root);

	return 0;
}
