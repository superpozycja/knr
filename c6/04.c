#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 100
#define MAXWORD 1000

char buf[BUFSIZE];
int bufp = 0;

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

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

struct tnode *addtree_word(struct tnode *p, char *w)
{
	int cond;
	if (p == NULL) {
		p = talloc();
		p->word = my_strdup(w);
		p->left = p->right = NULL;
		p->count = 1;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		p->count++;
	} else if (cond < 0) {
		p->left = addtree_word(p->left, w);
	} else {
		p->right = addtree_word(p->right, w);
	}

	return p;
}

struct tnode *addtree_count(struct tnode *p, char *w, int count)
{
	int cond;
	if (p == NULL) {
		p = talloc();
		p->word = my_strdup(w);
		p->left = p->right = NULL;
		p->count = count;
	} else if (p->count == count) {
		if (strcmp(w, p->word) < 0)
			p->left = addtree_count(p->left, w, count);
		else if (strcmp(w, p->word) > 0)
			p->right = addtree_count(p->right, w, count);
	} else if (p->count < count) {
		p->left = addtree_count(p->left, w, count);
	} else {
		p->right = addtree_count(p->right, w, count);
	}

	return p;
}

void treeprint(struct tnode *p)
{
	if (p) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

struct tnode *populate_counttree(struct tnode *p_word, struct tnode *p_count)
{
	if (p_word) {
		p_count = addtree_count(p_count, p_word->word, p_word->count);
		populate_counttree(p_word->left, p_count);
		populate_counttree(p_word->right, p_count);
	}

	return p_count;
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
	if (!isalpha(c)) {
		*w++ = '\0';
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
	char word[MAXWORD];
	struct tnode *root_word = NULL;
	struct tnode *root_count = NULL;

	while (getword(word, MAXWORD) != EOF) {
		root_word = addtree_word(root_word, word);
	}

	root_count = populate_counttree(root_word, root_count);
	treeprint(root_count);

	return 0;
}
