#include <stdio.h>
#include <unistd.h>
#define MAXLINE 1000
#define FOLD 20

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

/* TODO change to a function mutating s instead of just printing
 * you can just insert newlines where a dividing space would be 
 * 
 * this one is REALLY FUCKING UGLY */
void print_folded(char s[]) 
{
	int i = 0;
	int la = 0;
	int folded;
	while(s[i+la] != '\0') {
		folded = 0;
		while(s[i+la] != '\n' && s[i+la] != '\0')
			la++;
		int len = la;
		if(la >= FOLD) {
			folded = 1;
			while((la >= FOLD) || (s[i+la] != ' ' && s[i+la] != '\t' && la > 0))
				la--;
		}
		if(la == 0) {
			folded = 0;
			la = len;
		}
		int target = i + la;
		for(; i <= target; i++) {
			putchar(s[i]);
		}
		if(folded)
			putchar('\n');
		la = 0;
	}
}

int main()
{
	int len;
	char line[MAXLINE];
	while((len = my_getline(line, MAXLINE)) > 0) {
		print_folded(line);
	}
	return 0;
}
