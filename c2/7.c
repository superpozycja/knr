#include <stdio.h>

unsigned invert(unsigned x, unsigned p, unsigned n)
{
	/* ~(~0 << n) - mask first n bits	  
	 * (~(~0 << n) << p-n+1)) - mask bits to change
	 * x ^ ~(~(~0 << n) << p-n+1)) - invert masked bits
	 */

	return x ^ (~(~0 << n) << p-n+1);
}

int main()
{
	unsigned x = 0xff;
	x = invert(x, 4, 3);
	printf("0x%02x\n", x);
}
