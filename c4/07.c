#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

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

void ungets(char s[])
{
	int i = 0;
	while(s[i] != '\0')
		i++;
	while (i >= 0)
		ungetch(s[i--]);
}

int main()
{
	int c;
	ungets("hello\n");
	while ((c = getch()) != '\n')
		putchar(c);
	putchar('\n');
	return 0;
}
