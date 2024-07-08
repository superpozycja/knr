#include <stdio.h>

int strend(char *s, char *t)
{
	char *tend = t;
	while (*tend != '\0')
		tend++;
	while (*s != '\0')
		s++;
	while (tend != t)
		if (*s-- != *tend--)
			return 0;
	return 1;
}

int main()
{
	char s[] = "commotion";
	char t[] = "motion";
	char t2[] = "demotion";
	printf("%d\n", strend(s, t));
	printf("%d\n", strend(s, t2));
}
