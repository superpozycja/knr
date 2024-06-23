#include <stdio.h>

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y)
{
	/* ~(~0 << n) - mask first n bits	  
	 * ~(~(~0 << n) << p-n+1)) - mask bits that dont change
	 * x & ~(~(~0 << n) << p-n+1)) - clear bits to change
	 *
	 * y & ~(~0 << n) - get first n bits of y 
	 * y & ~(~0 << n) << p-n+1 - move first n bits of y by offset p 
	 * 
	 * then by doing | we add cleared bits from x to moved bits of y
	 */


	return (x & ~(~(~0 << n) << p-n+1)) | ((y & ~(~0 << n)) << p-n+1);
}

int main()
{
	unsigned x = 0xce;
	unsigned y = 0x05;
	x = setbits(x, 4, 3, y);
	printf("0x%02x\n", x);
}
