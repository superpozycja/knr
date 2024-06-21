#include <stdio.h>

#define TAB_SIZE 8

int main() {
	int c;
	int spaces = 0;
	while((c = getchar()) != EOF) {
		if(c == ' ') {
			spaces++;
			if(spaces == TAB_SIZE) {
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

