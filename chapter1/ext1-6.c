/*A program verify the output of getchar() != EOF is 0 or 1*/

#include <stdio.h>

int main()
{
	int c;

	printf("getchar() != EOF: %d \n", c = getchar() != EOF);

	return 0;
}
