#include <stdio.h>
#include <stdarg.h>

void minscanf(char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	int *ival;
	float *dval;
	va_start(ap, fmt);

	for (p = fmt; *p; p++) {
		if (*p != '%') {
			continue;
		}
		switch (*++p) {
		case 'd':
			ival = va_arg(ap, int *);
			scanf("%d", ival);
			break;
		case 'f':
			dval = va_arg(ap, float *);
			scanf("%f", dval);
			break;
		case 's':
			sval = va_arg(ap, char *);
			scanf("%s", sval);
			break;
		default:
			break;
		}
	}

	va_end(ap);
}

int main()
{
	int d;
	float f;
	char s[100];
	minscanf("%d/%f%s", &d, &f, s);
	printf("%d\n", d);
	printf("%f\n", f);
	printf("%s\n", s);
}
