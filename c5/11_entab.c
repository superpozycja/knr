#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
	if (argc < 2)
		return 0;
	int c;
	int spaces = 0;
	int tab_size = atoi(argv[1]);
	while((c = getchar()) != EOF) {
		if(c == ' ') {
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
		}
	}
}

