#include <stdio.h>
#define MAXLINE 1000

void my_strcat(char *s, char *t)
{
	while(*s != '\0')
		s++;
	while((*s++ = *t++) != '\0')
		;
}

int main()
{
	char s[MAXLINE] = "test1" ;
	char t[MAXLINE] = "test2";
	my_strcat(s, t);
	printf("%s\n", s);
}
