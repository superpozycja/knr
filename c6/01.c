/* comment */
#include <stdio.h>
#define asdf fdsa
#include <ctype.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 100
#define MAXWORD 1000

char buf[BUFSIZE];
int bufp = 0;

struct key {
	char *word;
	int count;
} keytab[] = {
	"#define", 0,
	"#include", 0,
	"*/", 0,
	"/*", 0,
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	"do", 0,
	"double", 0,
	"else", 0,
	"enum", 0,
	"extern", 0,
	"float", 0,
	"for", 0,
	"goto", 0,
	"if", 0,
	"int", 0,
	"long", 0,
	"register", 0,
	"return", 0,
	"short", 0,
	"signed", 0,
	"sizeof", 0,
	"static", 0,
	"struct", 0,
	"switch", 0,
	"typedef", 0,
	"union", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0,
};

#define NKEYS (sizeof keytab / sizeof(keytab[0]))

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

int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, mid, high;

	low = 0;
	high = n-1;
	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int main()
{
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) || word[0] == '/' || word[0] == '#' || word[0] == '*')
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;

	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	return 0;
}
