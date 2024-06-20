#include <stdio.h>

int main() {
	int c;
	int in = 0;
	while((c = getchar()) != EOF) {
		if(c == ' ' || c == '\n' || c == '\t') {
			in = 0;
		}
		else if(!in){
			putchar('\n');
			in = 1;
		}
		if(in) {
			putchar(c);
		}
	}
	putchar('\n');
	return 0;
}

