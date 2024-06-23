#include <stdio.h>
#define ARR_SIZE 1000000

int binsearch(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low < high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid;
		else
			low = mid + 1;
	}
	if (v[mid] == x)
		return mid;
	return -1;
}

int main()
{
	int to_search[ARR_SIZE];
	for (int i = 0; i < ARR_SIZE; i++)
		to_search[i] = i;
	printf("%d\n",binsearch(1234, to_search, ARR_SIZE));
	return 0;
}
