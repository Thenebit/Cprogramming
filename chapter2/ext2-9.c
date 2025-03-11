/*Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the
rightmost 1-bit in x. Explain why. Use this observation to write a faster
version of bitcount. 
*/

#include <stdio.h>

/*bitcount: delete the rightmost 1-bit in x*/
int bitcount(unsigned x)
{
	int b = 0;

	while(x != 0){
		x &= (x - 1);
		b++;
	}
	return b;
}

int main()
{
	unsigned x = 29;

	int bitt = bitcount(x);

	printf("%u\n", bitt);

	return 0;
}
