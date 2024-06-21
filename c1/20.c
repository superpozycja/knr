#include <stdio.h>

#define TAB_SIZE 8

int main() {
	int c;
	int tab_cnt = 0;
	while((c = getchar()) != EOF) {
		if(c == '\t') {
			do {
				putchar(' ');
			} while((++tab_cnt % TAB_SIZE) != 0);
		}
		else {
			tab_cnt++;
			putchar(c);
			if(c == '\n')
				tab_cnt = 0;
		}
	}
}

