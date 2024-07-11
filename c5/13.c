#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 1000

#define ALLOCSIZE 10000

char membuf[ALLOCSIZE];
char *memp = membuf;

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

void memput(char *s, int len)
{
	strcpy(memp, s);
	memp += len;
}

void rmemput(char *s, int len, int d_len)
{
	strcpy(membuf, membuf+d_len);
	memp -= d_len;
	memput(s, len);
}

int main(int argc, char *argv[])
{
	int n = 10;
	while (--argc > 0 && (*++argv)[0] == '-')
		n = atoi(++argv[0]);
	if (argc != 0)
		printf("usage: tail -n\n");
	else {
		char line[MAXLINE];
		int len;
		int i = 0;
		int exceeded = 0;
		int lens[n];
		while ((len = my_getline(line, MAXLINE)) != 0) {
			int evicted = lens[i];
			lens[i] = len;
			if (exceeded)
				rmemput(line, len, evicted);
			else
				memput(line, len);
			i++;
			if (i == n) 
				exceeded = 1;
			i %= n;
		}
		printf("%s", membuf);
	}
	return 0;

}
