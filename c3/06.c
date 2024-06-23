#include <stdio.h>
#include <limits.h>
#define MAXLINE 1000

void reverse(char s[], int len)
{
	len -= 1;
	for (int i = 0; i < (len+1)/2; i++) {
		char tmp = s[i];
		s[i] = s[len - i];
		s[len - i] = tmp;
	}
}

void itoa(int n, char s[], int w)
{
	int i, sign;
	unsigned un;
	un = n;
	if ((sign = n) < 0)
		un = -n;
	i = 0;
	do {
		s[i++] = un % 10 + '0';
	} while ((un /= 10) > 0);

	if (sign < 0)
		s[i++] = '-';

	while(i < w)
		s[i++] = ' ';

	s[i] = '\0';
	reverse(s, i);
}

int main()
{
	int n = 1234;
	char s[MAXLINE];
	itoa(n, s, 10);
	printf("%s\n", s);
	printf("01234567890123456789\n");
	return 0;
}
