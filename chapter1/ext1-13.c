/*A program to print the length of each words in  its inputs*/

#include <stdio.h>
#define IN (1)
#define OUT (0)

int main()
{
	int c, nw, state, wl;

	nw = 0;
	state = OUT;
	wl = 0;

	while((c = getchar()) != EOF){
		if(c == ' ' || c == '\n' || c == '\t'){
			if(state == IN ){
				printf("Length of word in input %d: %d\n", nw, ++wl);
				wl = 1; 	/*track when inside a word*/
			}
			state = OUT;
		}else{
			if(state == OUT){
				state = IN;
				++nw;
			}
			++wl;
		}
	}

	printf("Total words in input: %d\n", nw);

	return 0;
}
