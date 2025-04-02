// Exercise 8-6. The standard library function calloc(n,size) returns a pointer 
// to n objects of
// size size, with the storage initialized to zero. Write calloc, by calling 
// malloc or by
// modifying it.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// calloc - allocate memory and initialize to zero.
void *calloc(size_t n, size_t size)
{
	size_t total_size = n * size;

	// handle multiplication overflow
	if(n != 0 && total_size / n != size)
		return NULL;

	void *ptr = malloc(total_size);

	if(ptr == NULL)
		return NULL;
	memset(ptr, 0, total_size);

	return ptr;
}

int main(void)
{
	int *arr = (int *)calloc(5, sizeof(int));

	if(arr == NULL){
		printf("Memory allocation failed.\n");

		return 1;
	}

	for(int i = 0; i < 5; i++)
		printf("%d\n", arr[i]);

	free(arr);

	return 0;
}
