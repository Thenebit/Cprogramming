//Exercise 8-7. malloc accepts a size request without checking its 
//plausibility; free believes that the block it is asked to free contains a 
//valid size field. Improve these routines so they take more pains with error 

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NALLOC (1024) // minimum #units to request

//block header
union header
{
        struct {
                union header *ptr; // next block if on free list
                unsigned size;	   // size of this block
        } s;

        long x;
};

static union header base; //empty list to get started

static union header *freep = NULL; // start of free list

static union header *morecore(unsigned nu);

void my_free(void *ap); //my_free: put block ap in free list

//malloc: general-purpose storage allocator
void *my_malloc(unsigned nbytes)
{

        union header *p, *prevp;
        unsigned nunits;

        nunits = (nbytes + sizeof(union header) - 1) / sizeof(union header) + 1;

        // incase of any multiplication overflow
        if ((prevp = freep) == NULL) {

                base.s.ptr = freep = prevp = &base;

                base.s.size = 0;
        }

        // search for a free block
        for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {

                if (p->s.size >= nunits) {

                        if (p->s.size == nunits) {

                                prevp->s.ptr = p->s.ptr;
                        } else {


                                p->s.size -= nunits;
                                p += p->s.size;
                                p->s.size = nunits;
                        }

                        freep = prevp;

                        return (void *)(p + 1);
                }

                // to avoid infinite loop
                if (p == freep) {

                        if ((p = morecore(nunits)) == NULL) {

                                return NULL;
                        }
                }
        }
}

 //morecore - ask system for more memory
static union header *morecore(unsigned nu)
{

        char *cp;
        union header *up;

        // handle multiplication overflow
        if (nu < NALLOC) {

                nu = NALLOC;

                cp = (char *)sbrk(nu * sizeof(union header));

                if (cp == (char *)-1) {

                        return NULL;
                }
        }


        up = (union header *)cp;
        up->s.size = nu;
        my_free((void *)(up + 1));

        return freep;
}

 //my_free - Free allocated memory
void my_free(void *ap)
{

        union header *bp;
        union header *p; // pointer to free block

        // point to block header
        bp = (union header *)ap - 1;

        for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {

                if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {

                        break;
                }
        }

        // join to upper neighbor
        if (bp + bp->s.size == p->s.ptr) {

                bp->s.size += p->s.ptr->s.size;
 
                bp->s.ptr = p->s.ptr->s.ptr;
        } else {

                bp->s.ptr = p->s.ptr;
        }

        // join to lower neighbor
        if (p + p->s.size == bp) {

                p->s.size += bp->s.size;

                p->s.ptr = bp->s.ptr;
        } else {

                p->s.ptr = bp;
        }

        freep = p;
}

//my_calloc -  and initialize to zero.
void *my_calloc(size_t n, size_t size)
{

        void *p;


        if ((p = my_malloc(n * size)) == NULL) {
                return NULL;
        }


        for (size_t i = 0; i < n * size; i++) {
                *((char *)p + i) = 0;
        }

        return p;
}


int main(void)
{
        int *p = my_calloc(10, sizeof(int));

        // print allocated memory
        for (int i = 0; i < 10; i++) {
                printf("%d\n", p[i]);
        }

        my_free(p);

        return 0;
}
