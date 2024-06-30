#include <ctype.h>
#include <stdio.h>
#define MAXLINE 1000

int mygetline(char s[], int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

double atof(char s[])
{
	double val, power, e_multiplr;
	int i, sign, e_pow;

	for (i = 0; isspace(s[i]); i++)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	/* or use tolower() whatever hurr burr */
	if (s[i] == 'e' || s[i] == 'E')
		i++;

	e_multiplr = (s[i] == '-') ? 10 : 0.1;
	if (s[i] == '+' || s[i] == '-')
		i++;

	for (e_pow = 0; isdigit(s[i]); i++)
		e_pow = 10.0 * e_pow + (s[i] - '0');

	for (int j = 0; j < e_pow; j++)
		power *= e_multiplr;
	return sign * val / power;
}

int main()
{
	/* unironically who writes like this */
	double sum, atof(char []);
	char line[MAXLINE];
	int mygetline(char line[], int max);

	sum = 0;
	while (mygetline(line, MAXLINE) > 0)
		printf("\t%f\n", sum += atof(line));
	return 0;
}
