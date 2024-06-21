#include <stdio.h>

/* as per ascii */
#define MAX_LEN 255

int main() {
	int lens[MAX_LEN];
	int c;

	for(int i = 0; i < MAX_LEN; i++) {
		lens[i] = 0;
	}

	while((c = getchar()) != EOF) {
		lens[c]++;
	}

	int max_occ = 0;

	for(int i = 0; i < MAX_LEN; i++) {
		if(lens[i] > max_occ)
			max_occ = lens[i];
	}

	for(int i = max_occ; i >= 0; i--) {
		for(int j = 0; j < MAX_LEN; j++) {
			if(lens[j] >= i)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
	return 0;
}

