// Exercise 8-8. Write a routine bfree(p,n) that will free any arbitrary block 
// p of n characters
// into the free list maintained by malloc and free. By using bfree, a user can 
// Add a static or
// external array to the free list at any time.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define NALLOC 1024 // Number of units to allocate

union header
{
        struct {
                union header *ptr; // Next free block
                unsigned size;	   // Size of this block
        } s;

        long x;
};

static union header *freep = NULL; // Pointer to start of free list

 //bfree - Free a block of memory
void bfree(void *p, unsigned n)
{

        union header *bp;

        // to ensure the block is large enough to hold a header
        if(n < sizeof(union header))
                return;

        bp = (union header *)p;

        bp->s.size = n / sizeof(union header);
        bp->s.ptr = freep;

        freep = bp;
}


int main(void)
{
        char static_memory[NALLOC * sizeof(union header)];

        bfree(static_memory, sizeof(static_memory));

        int *arr = (int *)malloc(5 * sizeof(int));
        if (arr == NULL) {
                printf("Memory allocation failed.\n");
                return 1;
        }

        for (int i = 0; i < 5; i++) {
                arr[i] = i * i;
                printf("%d ", arr[i]);
        }

        printf("\n");

        free(arr);

        return 0;
}
