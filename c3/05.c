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

void itob(int n, char s[], int b)
{
	int i, sign;
	unsigned un;
	un = n;
	if ((sign = n) < 0)
		un = -n;
	i = 0;
	do {
		if (un % b <= 9)
			s[i++] = un % b + '0';
		else 
			s[i++] = un % b + 'a' - 10;

	} while ((un /= b) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s, i);
}

int main()
{
	int n = INT_MIN;
	char s[MAXLINE];
	itob(n, s, 16);
	printf("%s\n", s);
	return 0;
}
