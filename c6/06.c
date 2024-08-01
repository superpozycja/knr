#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define BUFSIZE 100
#define MAXWORD 1000

char buf[BUFSIZE];
int bufp = 0;
static struct nlist *hashtab[HASHSIZE];

int my_getline(char *s, int lim)
{
	int c;
	char *tmp = s;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return s - tmp;
}

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

unsigned int hash(char *s)
{
	unsigned int hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	return NULL;
}

char *my_strdup(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s)+1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned int hashval;
	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(struct nlist));
		if (np == NULL || (np->name = my_strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else {
		free((void *) np->defn);
	}
	if ((np->defn = my_strdup(defn)) == NULL)
		return NULL;
	return np;
	
}

struct nlist *undef(char *name)
{
	struct nlist *np;
	if ((np = lookup(name)) != NULL) {
		free((void *) np->defn);
		hashtab[hash(name)] = np->next;
		free((void *) np);
		return NULL;
	}
	return np;
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
		putchar(c);
	if (c != EOF)
		*w++ = c;
	if (!isalnum(c) && c != '#') {
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
	struct nlist *l;
	char word[MAXWORD];
	char word_install[MAXWORD];
	int ins = 0;
	int skip = 0;
	while (getword(word, MAXWORD) != EOF) {
		if (skip) {
			if (word[0] == '"')
				skip = 0;
			printf("%s", word);
			continue;
		}
		if (word[0] == '"')
			skip = 1;

		l = lookup(word);

		if (l)
			printf("%s", l->defn);
		else
			printf("%s", word);

		switch (ins) {
		case 0:
			if (strcmp(word, "#define") == 0)
				ins = 1;
			break;
		case 1:
			strcpy(word_install, word);
			ins = 2;
			break;
		case 2:
			l = install(word_install, word);
			ins = 0;
			break;
		default:
			break;
		}
	}
}
