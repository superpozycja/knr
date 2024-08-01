#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("invalid args\n");
		return 1;
	}
	FILE *fp1;
	FILE *fp2;
	char line1[MAXLINE];
	char line2[MAXLINE];
	int linec = 0;
	if (((fp1 = fopen(argv[1], "r")) == NULL) || ((fp2 = fopen(argv[2], "r")) == NULL)) {
		printf("file open error\n");
		return 1;
	}
	while (fgets(line1, MAXLINE, fp1) && fgets(line2, MAXLINE, fp2)) {
		linec++;
		if (strcmp(line1, line2) != 0) {
			printf("differing at line %d\n", linec);
			printf("%s: %s", argv[1], line1);
			printf("%s: %s", argv[2], line2);
			break;
		}
	}
	fclose(fp1);
	fclose(fp2);
}
