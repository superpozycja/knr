#include <stdio.h>
#define MAXLINE 100

/* kinda ugly, but this problem is ugly so this gets a pass */
void itoa(int n, char s[])
{
	if (n == 0)
		s[0] = '\0';
	else {
		itoa(n/10, s);
		int i = 0;
		while (s[i] != '\0')
			i++;
		s[i] = n % 10 + '0';
	}
}

int main()
{
	char s[MAXLINE];
	itoa(1000, s);
	printf("%s\n", s);
	return 0;
}
