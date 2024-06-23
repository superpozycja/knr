#include <stdio.h>
#define MAXLINE 1000

void escape(char s[], char t[])
{
	int i = 0;
	int j = 0;
	while (t[i] != '\0') {
		switch (t[i]) {
		case '\n':
			s[j++] = '\\';
			s[j++] = 'n';
			break;
		case '\t':
			s[j++] = '\\';
			s[j++] = 't';
			break;
		default:
			s[j++] = t[i];
			break;
		}
		i++;
	}
	s[j] = '\0';

}

void descape(char s[], char t[])
{
	int i = 0;
	int j = 0;
	int escaped = 0;
	while (t[i] != '\0') {
		if (escaped) {
			switch (t[i]) {
			case 'n':
				s[j++] = '\n';
				break;
			case 't':
				s[j++] = '\t';
				break;
			default:
				s[j++] = '\\';
				s[j++] = t[i];
				break;
			}
			escaped = 0;
		}
		else {
			switch (t[i]) {
			case '\\':
				escaped = 1;
				break;
			default:
				s[j++] = t[i];
				break;
			}
		}
		i++;
	}
}

int main()
{
	char s[MAXLINE];
	char t[MAXLINE] = "this is a	test\nyeah";
	char s2[MAXLINE];
	printf("%s\n", t);

	escape(s,t);
	printf("%s\n", s);

	descape(s2, s);
	printf("%s\n", s2);
}
