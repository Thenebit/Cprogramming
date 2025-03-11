/*Exercise 3-1. Our binary search makes two tests inside the loop,
 when one would suffice (at the price of more tests outside).
 Write a version with only one test inside the loop and measure the
 difference in run-time.
*/

#include <stdio.h>

/*binsearch: binsearch decides if value of x occurs in sorted array v */
int binsearch(int x, int v[], int n)
{
	int low, mid, high;

	low = 0;
	high = n - 1;
	while(low <= high){
		mid = (low + high) / 2;
		//Using a single test to find value of x in v[]
		if(x == v[mid]){
			return mid;
		}
		(x < v[mid]) ? (high = mid - 1) : (low = mid + 1);
	}
	return -1;	//no match
}

int main()
{
	int x, n;
	int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int result;

	x = 2;
	n = 10;

	result = binsearch(x, v, n);
	printf("Middle element is: %d\n", result);

	return 0;
}
