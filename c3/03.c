#include <stdio.h>
#define MAXLINE 1000

void expand(char s1[], char s2[])
{
	int i = 0;
	int j = 0;
	while (s1[i] != '\0') {
		if (s1[i] == '-' && i > 0 && s1[i+1] != '\0') {
			for(int z = s1[i-1]+1; z < s1[i+1]; z++)
				s2[j++] = z;
		}
		else {
			s2[j++] = s1[i];
		}
		i++;
	}
	s2[j] = '\0';
}

int main()
{
	char s1[MAXLINE] = "a-b-c";
	char s2[MAXLINE] = "a-z0-9";
	char s3[MAXLINE] = "-a-z";
	char res[MAXLINE];

	expand(s1, res);
	printf("%s\n", res);
	expand(s2, res);
	printf("%s\n", res);
	expand(s3, res);
	printf("%s\n", res);
	return 0;
}
