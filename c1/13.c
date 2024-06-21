#include <stdio.h>

#define MAX_LEN 50	/* the longest is actually 45 but lets give ourselves
			 * some padding */

int main() {
	int lens[MAX_LEN];

	for(int i = 0; i < MAX_LEN; i++) {
		lens[i] = 0;
	}

	int max_len = 0;
	int n = 0;
	int c;
	int in = 0;
	while((c = getchar()) != EOF) {
		if(c == ' ' || c == '\n' || c == '\t') {
			if(n) {
				lens[n]++;
				if(n > max_len) {
					max_len = n;
				}
				n = 0;
				in = 0;
			}
		}
		else if(!in){
			in = 1;
		}
		else if(in) {
			n++;
		}
	}
	int max_occ = 0;

	for(int i = 0; i < max_len; i++) {
		if(lens[i] > max_occ)
			max_occ = lens[i];
	}

	for(int i = max_occ; i >= 0; i--) {
		for(int j = 0; j < max_len; j++) {
			if(lens[j] >= i)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
	return 0;
}

