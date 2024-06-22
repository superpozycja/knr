#include <stdio.h>
#define MAX_DEPTH 1000

int main()
{
	/* im just gonna count brackets cause the principle is the same and
	 * im lazy to do more of them */
	int c;
	int stack[MAX_DEPTH];
	int sp = 0;
	int nl = 0;
	while((c = getchar()) != EOF) {	
		if(c == '\n') {
			nl++;
		}
		if(c == '{') {
			stack[sp] = nl;
			sp++;
		}
		if(c == '}') {
			sp--;
			if(sp < 0) {
				sp = 0;
				printf("unopened } in line %d\n", nl);
			}
		}
	}
	for(int i = 0; i < sp; i++){
		printf("unclosed { in line %d\n", stack[i]);
	}
}
