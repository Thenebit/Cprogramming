/*2-6. Write a function setbits(x,p,n,y) that returns x with the n bits 
that begin at position p set to the rightmost n bits of y, leaving the other
 bits unchanged.
*/

#include <stdio.h>

/*setbits: setting x bits to rightmost bits of y*/
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	unsigned maskBits = ~(~0 << n) << (p + 1 - n);
	x &= ~maskBits;

	unsigned setYbits = (y & ~(~0 << n));

	return x | (setYbits << (p + 1 - n));
}

int main()
{
	unsigned x;
	unsigned y;
	int p;
	int n;

	x = 29;
	y = 15;
	p = 4;
	n = 3;

	unsigned bitw =  setbits(x, p, n, y);

	printf("Extracted bits %u\n", bitw);

	return 0;
}

