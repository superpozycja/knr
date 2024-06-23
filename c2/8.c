#include <stdio.h>

/* this assumees 32-bit int */
unsigned rightrot(unsigned x, unsigned n)
{
	/* ~(~0 << n) - mask first n bits	  
	 * (x & ~(~0 << n)) - get first n bits
	 * (x & ~(~0 << n) << 32-n) - place the first bits at the front
	 * (rest of bits is 0)
	 *
	 * x >> n - just rot non circularly
	 * ((x & ~(~0 << n)) << 32-n) | (x >> n) - rot and replace the bits
	 * lost during x>>n
	 */

	return ((x & ~(~0 << n)) << 32-n) | (x >> n);
}

int main()
{
	unsigned x = 0xff;
	x = rightrot(x, 5);
	printf("0x%x\n", x);
}
