#include <stdio.h>

int main() {
	int c;
	int in = 0;
	while((c = getchar()) != EOF) {
		if(c != ' ')
			in = 0;
		if(!in)
			putchar(c);
		if(c == ' ')
			in = 1;
	}
	return 0;
}

