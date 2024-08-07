/* stolen from [1], i got too angry at this, skill issue on my part 
 *
 * [1] https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_5:Exercise_18
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 100
#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS};

char buf[BUFSIZE];
int bufp = 0;
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

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

int gettoken(void)
{
	int c;
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else {
		return tokentype = c;
	}
}

int dirdcl(void);

int dcl(void)
{
	int ns;
	for (ns = 0; gettoken() == '*'; )
		ns++;
	if (dirdcl() == 1)
		return 1;
	while (ns-- > 0)
		strcat(out, " pointer to");
	return 0;
}

int dirdcl(void)
{
	int type;

	if (tokentype == '(') {
		if (dcl() == 1)
			return 1;
		if (tokentype != ')') {
			printf("error: missing )\n");
			return 1;
		}
	} else if (tokentype == NAME) {
		strcpy(name, token);
	} else {
		printf("error: expected name or (dcl)\n");
		return 1;
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS) {
			strcat(out, " function returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	return 0;
}

int main()
{
	while (gettoken() != EOF) {
		strcpy(datatype, token);
		out[0] = '\0';
		if (dcl() == 0 && tokentype == '\n') {
			printf("%s: %s %s\n", name, out, datatype);
		}
		else {
			printf("syntax error\n");
			for (int c = 0; c != '\n' && c != EOF; )
				if ((c = getch()) == EOF)
					ungetch(c);
		}
	}
}
