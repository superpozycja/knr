#include <stdio.h>

int main() {
	int ns = 0;	/*  space  */
	int nt = 0;	/*   tab   */
	int nl = 0;	/* newline */

	int c;
	while((c = getchar()) != EOF) {
		if(c == ' ') ++ns;
		if(c == '\t') ++nt;
		if(c == '\n') ++nl;
	}

	printf("spaces: %d\n", ns);
	printf("tabs: %d\n", nt);
	printf("newlines: %d\n", nl);
}

