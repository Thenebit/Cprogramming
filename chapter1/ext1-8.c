/*A program to count blanks, tabs, newlines*/

#include <stdio.h>
#define BLANK ' '
#define TAB '\t'
#define NEWLINE '\n'

int main()
{
	//bl is blank, tb is tabs, and nc is newline
	int c, bl, tb, nl;

	bl = tb = nl = 0;

	while((c = getchar()) != EOF){
		if(c == BLANK){
			++bl;
		}else if(c == TAB){
			++tb;
		}else if(c == NEWLINE){
			++nl;
		}
		printf("blanks: %d and tabs: %d and newline: %d\n", bl, tb, nl);
	}
	//if the printf() is here, will only see contents after termination

	return 0;
}
