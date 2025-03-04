/*A program to print the input words on different line*/

#include <stdio.h>
#define IN (1)
#define OUT (0)

int main()
{
	int c, nl, nc, nw, state;

	nl = nc = nw = 0;
	state = OUT;

	while((c = getchar()) != EOF){
		++nc;	/*increment character*/
		if(c == '\n'){
			++nl;	/*increment newline occurence*/
		}else if(c == ' ' || c == '\n' || c == '\t'){
			state = OUT;	/*outside of a word*/
		}else if(state == OUT){
			state = IN;	/*inside of a word*/
			++nw;
			putchar('\n'); /*Prints a newline before the word*/
			putchar(c);
		}else{ putchar(c);}
	}

	//printf("Newline: %d Character: %d Words: %d\n", nl, nc, nw);

	return 0;
}
