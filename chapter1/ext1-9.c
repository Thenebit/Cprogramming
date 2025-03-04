//A program to copy an input and replace double blanks with single blanks

#include <stdio.h>
#define SINGLEBLANK ' '

int main()
{
	int c;

	int bl = ' ';	/*variable to use to check for last character*/

	while((c = getchar()) != EOF){
		if(c == SINGLEBLANK){
			if(bl != ' '){
				putchar(SINGLEBLANK);
			}
		}else{ putchar(c);}

		bl = c;
	}

	return 0;
}
