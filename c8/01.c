#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void fdcopy(int f1, int f2)
{
	int n;
	char buf[BUFSIZ];
	while ((n = read(f1, buf, BUFSIZ)) > 0)
		if (write(f2, buf, n) != n)
			printf("write error on file\n");
}

int main(int argc, char *argv[])
{
	int fd;
	if (argc == 1)
		fdcopy(0, 1);
	else
		while (--argc > 0)
			if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
				printf("cant open file %s\n", *argv);
				return 1;

			} else {
				fdcopy(fd, 1);
				close(fd);
			}
	return 0;
}
