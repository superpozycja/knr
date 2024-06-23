#include <stdio.h>
#include <limits.h>

void squeeze(char s1[], char s2[])
{
	int occs[CHAR_MAX];
	for(int i = 0; i < CHAR_MAX; i++)
		occs[i] = 0;
	for(int i = 0; s2[i] != '\0'; i++)
		occs[s2[i]] = 1;

	int i, j;
	for(i = j = 0; s1[i] != '\0'; i++)
		if(occs[s1[i]] == 0)
			s1[j++] = s1[i];
	s1[j] = '\0';
}

int main()
{
	char s[] = "a quick brown fox jumped over a lazy dog";
	squeeze(s, "abd");
	printf("%s\n", s);
}
