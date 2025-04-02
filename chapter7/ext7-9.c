/* Exercise 7-9. Functions like isupper can be implemented to save space or to
 save time.
 Explore both possibilities.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX (1000000)

// Save space
int isupper_space(int c) {
	if(c >= 'A' && c<= 'Z')
		return 1;

	return 0;
}

// Save time
int isupper_time(int c) {
	if(c >= 65 && c <= 90)
		return 1;

	return 0;
}

int main(void)
{
	int c;
	clock_t start, end;
	double cpu_time_used;


	// Save space
	start = clock();

	for(int i = 0; i < MAX; i++){

		for(c = 0; c < 128; c++){
			isupper_space(c);
		}
	}
	end = clock();

	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	printf("isupper_space: %f\n", cpu_time_used);

	// Save time
	start = clock();

	for(int i = 0; i < MAX; i++){

		for(c = 0; c < 128; c++){
			isupper_time(c);
		}
	}
	end = clock();

	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	printf("isupper_time: %f\n", cpu_time_used);

	return 0;
}
