/* im not doing all those function im too lazy have just a getline instead */

#include <stdio.h>
#define MAXLINE 1000

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

int main()
{
	char line[MAXLINE];
	while (my_getline(line, MAXLINE) > 0)
		printf("%s", line);
		
	return 0;
}
