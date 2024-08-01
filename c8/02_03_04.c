#include "syscalls.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag.read && fp->flag.write) == 0)
			break;
	if (fp >= _iob + OPEN_MAX)
		return NULL;

	if (*mode == 'w') {
		fd = creat(name, 0755);
	} else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, 0755);
		lseek(fd, 0L, 2);
	} else {
		fd = open(name, O_RDONLY, 0);
	}
	if (fd == -1)
		return NULL;
	
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag.read = (*mode == 'r');
	fp->flag.write = !(fp->flag.read);
	return fp;
}

int _fillbuf(FILE *fp)
{
	int bufsize;

	if ((fp->flag.read && (fp->flag.eof)))
		return EOF;
	bufsize = (fp->flag.unbuf) ? 1 : BUFSIZ;
	if (fp->base == NULL)
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag.eof = 1;
		else
			fp->flag.err = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *fp)
{
	int n;
	int bufsize;
	if ((fp->flag.write && (fp->flag.err)))
		return EOF;
	bufsize = (fp->flag.unbuf) ? 1 : BUFSIZ;
	if (fp->base == NULL) {
		if ((fp->base = (char *) malloc(bufsize)) == NULL) { 
			fp->flag.err = 1;
			return EOF;
		}
	} else {
		n = fp->ptr - fp->base;
		if (write(fp->fd, fp->base, n) != n) {
			fp->flag.err = 1;
			return EOF;
		}
	}
	fp->ptr = fp->base;
	*fp->ptr++ = c;
	fp->cnt = bufsize - 1;
	return c;
}

int fflush(FILE *fp)
{
	int ret;
	if (fp->flag.write)
		ret = _flushbuf(0, fp);
	fp->ptr = fp->base;
	fp->cnt = (fp->flag.unbuf) ? 1 : BUFSIZ;
	return ret;
}

int fclose(FILE *fp)
{
	int ret;
	if ((ret = fflush(fp)) != EOF) {
		free(fp->base);
		fp->ptr = NULL;
		fp->cnt = 0;
		fp->base = NULL;
		fp->flag.read = 0;
		fp->flag.write = 0;
	}
	return ret;
}

int fseek(FILE *fp, long offset, int origin)
{
	int ret = -1;
	if (fp->flag.read) {
		if (origin == 1)
			offset -= fp->cnt;
		ret = lseek(fp->fd, offset, origin);
		
	} else if (fp->flag.write) {
		if(_flushbuf(0, fp) != EOF)
			lseek(fp->fd, offset, origin);
	}
	return ret == -1 || ret == EOF ? -1 : 0;
}

int main()
{

}
