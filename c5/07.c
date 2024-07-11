#include <stdio.h>
#include <string.h>
#define MAXLEN 1000
#define MAXLINES 1000
#define ALLOCSIZE 100000

char *lineptr[MAXLINES];

int my_getline(char *s, int lim)
{
	int c;
	char *tmp = s;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return s - tmp;
}

int readlines(char *lineptr[], int maxlines, char *s)
{
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;

	while ((len = my_getline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines)
			return -1;
		p = s;
		s += len;
		line[len-1] = '\0';
		strcpy(p, line);
		lineptr[nlines++] = p;

	}
	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

void swap(char *v[], int i, int j)
{
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void qsort(char *v[], int left, int right)
{
	int i, last;

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, left+1, right);
}

int main()
{
	int nlines;
	char s[ALLOCSIZE];

	if ((nlines = readlines(lineptr, MAXLINES, s)) >= 0) {
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}
