#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define ALLOCSIZE 1000
char *lineptr[MAXLINES];

char allocbuf[ALLOCSIZE];
char *allocp = allocbuf;

char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	} else
		return 0;
}

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

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;

	while ((len = my_getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
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

void swap(void *v[], int i, int j)
{
	void *tmp;
	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

void my_qsort(void *v[], int left, int right, 
	   int (*comp)(void *, void *), int reverse, int col)
{
	int i, last;

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++) {
		int tmp_col = 0;
		int off1 = 0;
		int off2 = 0;
		for(int t = 0; t < col; t++) {
			while(!isspace(((char *)v[i])[off1]))
				off1++;
			while(!isspace(((char *)v[left])[off2]))
				off2++;
		}
		if ((reverse) * (*comp)(v[i]+off1, v[left]+off2) < 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	my_qsort(v, left, last-1, comp, reverse, col);
	my_qsort(v, last+1, right, comp, reverse, col);
}

int numcmp(const char *s1, const char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	return 0;
}

int __tolower_cond(int c, int nocase)
{
	if (c == '\0') printf("segfault much?\n");
	return nocase ? tolower(c) : c;
}

int __dircmp(const char *s1, const char *s2, int nocase)
{
	int i = 0, j = 0;
	while(__tolower_cond(s1[i], nocase) == __tolower_cond(s2[j], nocase)) {
		int i_inc = 1;
		int j_inc = 1;
		while (s1[i] && !isalnum(__tolower_cond(s1[i], nocase)) && s1[i] != ' ') {
			i++;
			i_inc = 0;
		}
		while (s2[j] && !isalnum(__tolower_cond(s2[j], nocase)) && s2[j] != ' ') {
			j++;
			j_inc = 0;
		}
		if (s1[i] == '\0' || s2[j] == '\0')
			return 0;
		i += i_inc;
		j += j_inc;
	}
	return s1[i] - s2[j];
}

int dircmp(const char *s1, const char *s2)
{
	return __dircmp(s1, s2, 0);
}

int dircasecmp(const char *s1, const char *s2)
{
	return __dircmp(s1, s2, 1);
}

int main(int argc, char *argv[])
{
	int nlines;
	int c;
	int numeric = 0, reverse = 1, nocase = 0, dir = 0, col = 0;

	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
			case 'n':
				numeric = 1;
				break;
			case 'r':
				reverse = -1;
				break;
			case 'f':
				nocase = 1;
				break;
			case 'd':
				dir = 1;
				break;
			default:
				printf("illegal option%c\n", c);
				return -1;
			}

	if (argc > 0) 
		col = atoi(*argv);


	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		int (*fun)(void *, void *);

		if (numeric)
			fun = (int (*)(void *, void *)) numcmp;
		else if (dir) {
			if (nocase)
				fun = (int (*)(void *, void *)) dircasecmp;
			else
				fun = (int (*)(void *, void *)) dircmp;
		}
		else if (nocase)
			fun = (int (*)(void *, void *)) strcasecmp;
		else
			fun = (int (*)(void *, void *)) strcmp;		
		my_qsort((void **) lineptr, 0, nlines-1, fun, reverse, col);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}
