#include <stdio.h>

#define swap(t,x,y) { t TMP; TMP = x; x = y; y = TMP; }

int main()
{
	int a = 2;
	int b = 4;
	printf("a - %d, b - %d\n", a, b);
	swap(int, a, b);
	printf("a - %d, b - %d\n", a, b);
}
