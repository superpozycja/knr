#include <stdio.h>

int buf = -1;

int getch(void)
{
	int ret = (buf >= 0) ? buf : getchar();
	buf = -1;
	return ret;
}

void ungetch(int c)
{
	if (buf >= 0)
		printf("buf occupied\n");
	else
		buf = c;
}

int main()
{
	ungetch('a');
	ungetch('b');
	putchar(getch());
	putchar('\n');
	return 0;
}
