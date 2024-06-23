#include <stdio.h>

/* x-1 will invert every bit until the first 1 from the right inclusive.
 * the -1 will try to subtract from the first bit, and will 'borrow' from the
 * higher bit until it encounters a 1, then all of the bits before the 1 will
 * be flipped to 1, and that one that stopped the domino effect will become 0.
 *
 * if we then and these, bits higher than the aforementioned 1 stay the same
 * in both numbers, and the lower bits are flipped in one of the numbers, and
 * given a & ~a = 0, they all get cleared. since all of them but the first 1
 * were zeroes by definition, only the 1 bit is affected - being cleared. */
int bitcount(unsigned x)
{
	int res = x > 0;
	while((x &= (x-1)) > 0)
		res++;
	return res;
}

int main()
{
	unsigned x = 0xa5;
	printf("%d\n", bitcount(x));
	x = 0x00;
	printf("%d\n", bitcount(x));
}
