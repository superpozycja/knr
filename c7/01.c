#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, void *argv[])
{
	int c;
	while ((c = getchar()) != EOF)
		putchar(strcmp(argv[0], "./BIG") == 0 ? toupper(c) : tolower(c));
	return 0;
}
