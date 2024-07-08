#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("too many characters in ungetch buf\n");
	else
		buf[bufp++] = c;
}

int getfloat(float *pn)
{
	double power, e_multiplr;
	int sign, e_pow;
	int c;

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	if (c == '.')
		c = getch();
	for (power = 1.0; isdigit(c); c = getch()) {
		*pn = 10.0 * *pn + (c - '0');
		power *= 10;
	}
	/* or use tolower() whatever hurr burr */
	if (c == 'e' || c == 'E')
		c = getch();

	e_multiplr = (c == '-') ? 10 : 0.1;
	if (c == '+' || c == '-')
		c = getch();

	for (e_pow = 0; isdigit(c); c = getch())
		e_pow = 10.0 * e_pow + (c - '0');

	for (int j = 0; j < e_pow; j++)
		power *= e_multiplr;
	*pn = sign * *pn / power;
}

int main()
{
	float x;
	getfloat(&x);
	printf("%f\n", x);
}
