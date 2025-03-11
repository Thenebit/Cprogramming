/*Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits
that begin at position p inverted (i.e., 1 changed into 0 and vice versa),
leaving the others unchanged.
*/

#include <stdio.h>

/*invert: inverting the bits of x at position p*/
int invert(unsigned x, int p, int n)
{
	unsigned maskBits = ~(~0 << n) << (p + 1 -n);

	return x ^ maskBits;
}


int main()
{
	unsigned x;
	int p;
	int n;

	x = 15;
	p = 4;
	n = 3;

	unsigned bitw = invert(x, p, n);

	printf("Inverted bits: %u\n", bitw);

	return 0;
}
