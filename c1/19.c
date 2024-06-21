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

void copy(char to[], char from[])
{
	int i = 0;
	while((to[i] = from[i]) != '\0')
		++i;
}

void reverse(char s[], int len)
{
	len-=2;
	for(int i = 0; i < len/2; i++) {
		char tmp = s[i];
		s[i] = s[len-i];
		s[len-i] = tmp;
	}
}

int main()
{
	int len;
	char line[MAXLINE];
	while((len = my_getline(line, MAXLINE)) > 0) {
		reverse(line, len);
		printf("%s", line);
	}
	return 0;
}
