#include <stdio.h>

int lower(int c)
{
	return c + ((c >= 'A' && c <= 'Z') ? 'a' - 'A' : 0);
}

int main()
{
	char c = 'c';
	printf("%c\n", lower(c));
}
