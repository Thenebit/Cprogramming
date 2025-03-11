/*Exercise 2-1. Write a program to determine the ranges of char, short, int,
   and long variables both signed and unsigned, by printing appropriate
   values from standard headers and by direct computation. Harder if you
    compute them: determine the ranges of the various floating point types
*/

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
	printf("Data Types ranges for both Unsigned and Signed\n\n");

	/*Using the direct way by importing the libraries*/
	printf("Signed char = %d to %d\n", SCHAR_MIN, SCHAR_MAX);
	printf("Unsigned char = 0 to %d\n",  UCHAR_MAX);

	printf("Signed short = %d to %d\n", SHRT_MIN, SHRT_MAX);
	printf("Unsigned short = 0 to %d\n", USHRT_MAX);

	printf("Signed int = %d to %d\n", INT_MIN, INT_MAX);
	printf("Unsigned int = 0 to %d\n", UINT_MAX);

	printf("Signed long = %ld to %ld\n", LONG_MIN, LONG_MAX);
	printf("Unsigned long = 0 to %lu\n", ULONG_MAX);

	printf("\nFloating-point types\n\n");

	printf("Float = %e to %e\n", FLT_MIN, FLT_MAX);
	printf("Double = %e to %e\n", DBL_MIN, DBL_MAX);
	printf("Long double = %Le to %Le\n", LDBL_MIN, LDBL_MAX);

	/*Using the computation approach*/
	printf("\nComputational Approcah\n\n");
	printf("Signed char = %d to %d\n", -(1 << (sizeof(char)*8-1)),
		(1 << (sizeof(char)*8-1)) -1);
	printf("Unsigned char = 0 to %u\n", (1U << (sizeof(char)*8)) -1);
	printf("Signed short = %d to %d\n", -(1 << (sizeof(short)*8-1)),
		(1 << (sizeof(short)*8-1)) -1);
	printf("Unsigned short = 0 to %u\n", (1U << (sizeof(short)*8)) -1);
	printf("Signed int = %d to %d\n", (1 << (sizeof(int)*8-1)),
		(1U << (sizeof(int)*8-1)) -1);
	printf("Unsigned int = 0 to %u\n", (1U << (sizeof(int)*8-1))*2-1);
	printf("Signed long = %ld to %ld\n", (1L << (sizeof(long)*8-1)),
		(1UL << (sizeof(long)*8-1)) -1);
	printf("Unsigned long = 0 to %lu\n", (1UL << (sizeof(long)*8-1))*2-1);

	return 0;
}
