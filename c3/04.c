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

/* int is -(2^(w-1)) to 2^(w-1)-1
 * if we flip INT_MIN, we get 2^(w-1), which is 1 out of range
 * just swapping n to long wont fix the issue if int = long on the computer,
 * but since we always force n to be positive we can just store it in another
 * unsigned variable which will have 2^(w) and clearly 2^(w-1) < 2^(w)
 */
void itoa(int n, char s[])
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
	s[i] = '\0';
	reverse(s, i);
}

int main()
{
	int n = INT_MIN;
	char s[MAXLINE];
	itoa(n, s);
	printf("%s\n", s);
	return 0;
}
