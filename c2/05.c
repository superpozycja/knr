#include <stdio.h>
#include <limits.h>

int any(char s1[], char s2[])
{
	int occs[CHAR_MAX];
	for(int i = 0; i < CHAR_MAX; i++)
		occs[i] = 0;
	for(int i = 0; s2[i] != '\0'; i++)
		occs[s2[i]] = 1;

	for(int i = 0; s1[i] != '\0'; i++)
		if(occs[s1[i]] != 0)
			return i;
	return -1;
}

int main()
{
	char s[] = "a quick brown fox jumped over a lazy dog";
	printf("%d\n", any(s, "*"));
	printf("%d\n", any(s, "x"));
}
