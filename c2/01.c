#include <stdio.h>
#include <float.h>
#include <limits.h>

int main()
{
	printf("unsigned char: %d to %d\n", CHAR_MIN, CHAR_MAX);
	printf("signed char: %d to %d\n", SCHAR_MIN, SCHAR_MAX);

	printf("unsigned int: %u to %u\n", -UINT_MAX-1, UINT_MAX);
	printf("signed int: %d to %d\n", INT_MIN, INT_MAX);

	printf("unsigned long: %lu to %lu\n", -ULONG_MAX-1, ULONG_MAX);
	printf("signed long: %ld to %ld\n", LONG_MIN, LONG_MAX);

	printf("unsigned long long: %llu to %llu\n", -ULLONG_MAX-1, ULLONG_MAX);
	printf("signed long long: %lld to %lld\n", LLONG_MIN, LLONG_MAX);

	/* we can just use - because thats like flipping the first bit in 
	 * iee754 */
	printf("float: %f to %f\n", -FLT_MAX, FLT_MAX);
	printf("double: %f to %f\n", -DBL_MAX, DBL_MAX);
	return 0;
}
