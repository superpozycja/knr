#include <stdio.h>
#define MAXLINE 1000

int my_getline(char s[], int lim)
{
	int c, i;
	for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if(c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* purposefuly long line no. 0x0000000000000000000000000000000000000000000000000000000000000000000000000000000000000001 */

int main()
{
	int len;
	char line[MAXLINE];
	while((len = my_getline(line, MAXLINE)) > 0)
		if(len > 80)
			printf("%s", line);
	return 0;
/* purposefuly long line no. 0x0000000000000000000000000000000000000000000000000000000000000000000000000000000000000002 */
}
