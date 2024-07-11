#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int c;
	int tab_cnt = 0;
	int tab_size = 3;
	int tab_start = 3;

	while (--argc > 0 && ((*++argv)[0] == '-' || (*argv)[0] == '+')) {
		int mode = *argv[0];
		*++argv[0];
		switch (mode) {
		case '+':
			tab_size = atoi(argv[0]);
			break;
		case '-':
			tab_start = atoi(argv[0]);
			break;
		default:
			printf("illegal option\n");
			argc = 0;
			break;
		}
	}
	printf("%d argc\n", argc);
	if (argc != 1)
		printf("usage: entab -n +m\n");
	else
		while ((c = getchar()) != EOF) {
			if (c == '\t' && tab_cnt >= tab_start) {
				do {
					putchar(' ');
				} while ((++tab_cnt % tab_size) != 0);
			}
			else {
				tab_cnt += (c == '\t') ? 4 : 1;
				putchar(c);
				if (c == '\n')
					tab_cnt = 0;
			}
		}
}

