#include <stdio.h>
#define MAXLINE 1000

int my_getline(char s[], int lim)
{
	int c, i;
	for(i = 0; i < lim-1; i++) {
		if((c=getchar()) == EOF)
			break;
		if(c == '\n')
			break;
		s[i] = c;

	}
	if(c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

int main()
{
	int len;
	char line[MAXLINE];
	while((len = my_getline(line, MAXLINE)) > 0)
		printf("%s", line);
	return 0;
}
