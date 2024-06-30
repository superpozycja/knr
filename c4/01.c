#include <stdio.h>
#define MAXLINE 1000

char pattern[] = "ould";

int mygetline(char s[], int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

int strindex(char s[], char t[])
{
	int i, j, k;
	int res;
	res = -1;
	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			res = i;
	}
	return res;
}

int main()
{
	char line[MAXLINE];
	while (mygetline(line, MAXLINE) > 0) {
		int last_ix = strindex(line, pattern);
		if (last_ix >= 0) {
			printf("last occurence at %d\n", last_ix);
		}
		else {
			printf("no occurence\n");
		}
	}
	return 0;
}
