#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc < 2)
		return 0;

	int c;
	int tab_cnt = 0;
	int tab_size = atoi(argv[1]);
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			do {
				putchar(' ');
			} while ((++tab_cnt % tab_size) != 0);
		}
		else {
			tab_cnt++;
			putchar(c);
			if (c == '\n')
				tab_cnt = 0;
		}
	}
}

