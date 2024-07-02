#include <stdio.h>

/* this is the sexiest function i have written so far in this */
void reverse(char s[])
{
	int i = 0;
	char tmp;
	while (s[i] != '\0')
		i++;
	if (i) {
		tmp = s[0];
		s[0] = s[i-1];
		s[i-1] = '\0';
		reverse(s+1);
		s[i-1] = tmp;
	}
}

int main()
{
	char s[] = "kajka";
	reverse(s);
	printf("%s\n", s);
	return 0;
}
