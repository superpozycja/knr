#include <stdio.h>
#define MAXLINE 1000
#define FOLD 14

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

void fold(char s[], int lim)
{
	if (lim < FOLD)
		return;

	/* find the first space on the left and right of the fold line
	 *
	 * if theres a space on the left, insert a newline and recurse for the
	 * rest of the string
	 *
	 * if theres no space on the left, we cant fold on this word, so go
	 * to the next best one */

	int l, r;
	l = r = FOLD;
	while(s[l] != ' ' && s[l] > 0)
		l--;
	while(s[r] != ' ' && s[r] < lim)
		r++;
	if(l > 0) {
		s[l] = '\n';
		fold(s+l, lim-l);
	} else
		fold(s+r, lim-r);
}
int main()
{
	int len;
	char line[MAXLINE];
	while((len = my_getline(line, MAXLINE)) > 0) {
		fold(line, len);
		printf("%s", line);
	}
	return 0;
}
