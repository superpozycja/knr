/* the line below has like 20 spaces after the > */
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

int strip(char s[], int len)
{
	len--;
	while(len >= 0 && (s[len] == ' ' || s[len] == '\t' || s[len] == '\n'))
		s[len--] = '\0';
	s[len+1] = '\n';
	return len;
}

void copy(char to[], char from[])
{
	int i = 0;
	while((to[i] = from[i]) != '\0')
		++i;
}

int main()
{
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];

	max = 0;
	printf("len │ contents\n");
	printf("────┼───────────\n");
	while((len = my_getline(line, MAXLINE)) > 0) {
		/* we aint counting the newline, but we cant modify the
		 * getline function because a line with only a newline would
		 * return 0 which is not what we want */
		if((len = strip(line, len)) > 0) {
			printf("%3d │ %s", len, line);
			if(len > max) {
				max = len;
				copy(longest, line);
			}
		}
	}
	if(max > 0)
		printf("\nlongest line:\n%3d | %s", max, longest);
	return 0;
}
