#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 1000

int main(int argc, char *argv[])
{
	char line[MAXLINE];
	long lineno = 0;
	int c, except = 0, number = 0, found = 0;
	char pattern[MAXLINE];

	while (--argc >0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				printf("illegal option %c\n", c);
				return 1;
			}
	strcpy(pattern, *(argv++));
	argc--;
	FILE *fp;
	while (argc-- > 0) {
		if ((fp = fopen(*argv, "r")) != NULL) {
			while (fgets(line, MAXLINE, fp) != NULL) {
				lineno++;
				if ((strstr(line, pattern) != NULL) != except) {
					printf("%s", *argv);
					if (number)
						printf(":%ld: ", lineno);
					printf("%s", line);
					found++;
				}
			}
		} else {
			printf("file open error\n");
			exit(1);
		}
		argv++;
	}
	return found;
}
