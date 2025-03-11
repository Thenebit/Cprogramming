/*Exercise 2-8. Write a function rightrot (x,n) that returns the value
of the integer x rotated to the right by n bit postions.
*/

#include <stdio.h>

/*rightrot: rotate bit of x to the right*/
unsigned rightrot(unsigned x, int n)
{
	int sizeOfbits = sizeof(x);
	n = n % sizeOfbits;

	unsigned bitsTorot = x & ((1U << n) - 1);

	unsigned shiftXright = x >> n;

	unsigned bitsTopos = bitsTorot << (sizeOfbits - n);

	return shiftXright | bitsTopos;
}

int main()
{
	unsigned x;
	int n;

	x = 29;
	n = 3;

	unsigned bitw =  rightrot(x, n);

	printf("rotating x: %u to right n: %d at position: %u\n", x, n, bitw);

	return 0;
}
