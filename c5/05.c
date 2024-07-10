#include <stdio.h>
#define MAXLINE 100

void my_strncpy(char *s, char *t, int n)
{
	int i = 1;
	while ((*s++ = *t++) != '\0' && i < n)
		i++;
	*s = '\0';
}

int my_strncmp(char *s, char *t, int n)
{
	int i = 1;
	for (; *s == *t; s++, t++, i++)
		if (*s == '\0' || i == n)
			return 0;
	return *s - *t;
}

void my_strncat(char *s, char *t, int n)
{
	int i = 1;
	while (*s != '\0' && i++ < n)
		s++;
	while ((*s++ = *t++) != '\0' && i < n)
		i++;
	*s = '\0';
}

int main()
{
	char s[MAXLINE] = "wow this is a test";
	char s2[MAXLINE] = "wow this is a test";
	char s3[MAXLINE] = "w";
	char t[MAXLINE] = "wowie";
	my_strncpy(s, t, 4);
	printf("%s\n", s);
	int a = my_strncmp(s2, t, 2);
	printf("%d\n", a);
	my_strncat(s3, t, 3);
	printf("%s\n", s3);
}
