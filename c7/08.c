#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void filecopy(FILE *ifp, FILE *ofp)
{
	int c;
	while ((c = getc(ifp)) != EOF)
		putc(c, ofp);
}

int main(int argc, char *argv[])
{
	int pageno = 0;
	FILE *fp;
	++argv;
	while (--argc > 0) {
		printf("------------------\n");
		printf("page %d: %s\n", pageno, *argv);
		if ((fp = fopen(*argv, "r")) != NULL) {	
			filecopy(fp, stdout);
			printf("------------------\n");
		} else {
			printf("file open error\n");
			exit(1);
		}
		pageno++;
		argv++;
	}
	return 0;
}
