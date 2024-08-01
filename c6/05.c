#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];

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

int main()
{
	struct nlist *l;
	l = install("a", "A");
	l = lookup("a");
	printf("%s\n", l->defn);
	l = undef("a");
	l = lookup("a");
	if (l == NULL)
		printf("not found\n");
}
