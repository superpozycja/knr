#include <stdio.h>
#include <string.h>
#define MAXLINE 1000
#define FOLD 20

/* "protected" getline, we sub nonprintables for hex */ 
int my_getline_prot(char s[], int lim)
{
	int c, i;
	for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		/* 0x20 is space hence < not <= */
		if (c < 0x20 && c != '\t') {
			char tmp[6];
			sprintf(tmp, "\\0x%02x", c);
			strcpy(s+i, tmp);
			i += 4;
		} else {
			s[i] = c;
		}
	}
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

	int l, r;
	l = r = FOLD;
	while (s[l] != ' ' && s[l] > 0)
		l--;
	while (s[r] != ' ' && s[r] < lim)
		r++;
	if (l > 0) {
		s[l] = '\n';
		fold(s+l, lim-l);
	} else
		fold(s+r, lim-r);
}
int main()
{
	int len;
	char line[MAXLINE];
	while ((len = my_getline_prot(line, MAXLINE)) > 0) {
		fold(line, len);
		printf("%s", line);
	}
	return 0;
}
