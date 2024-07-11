#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
	if (argc < 2)
		return 0;
        int c;
	int spaces = 0;
	int tab_size = 3;
	int tab_start = 3;
	int ix = 0;

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
	if (argc != 0)
		printf("usage: entab -n +m\n");
	else
		while((c = getchar()) != EOF) {
			ix++;
			if(c == ' ' && ix >= tab_start) {
				spaces++;
				if(spaces == tab_size) {
					putchar('\t');
					spaces = 0;
				}
			}
			else {
				for(int i = 0; i < spaces; i++)
					putchar(' ');
				spaces = 0;
				putchar(c);
				if (c == '\n')
					ix = 0;
			}
		}
}

