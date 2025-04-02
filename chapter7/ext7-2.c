/*Exercise 7-1. Write a program that will print arbitrary input in a sensible 
 way. As a minimum, it should print non-graphic characters in octal or 
 hexadecimal according to local custom, and break long text lines.
*/

#include <stdio.h>
#include <ctype.h>

#define OCTLEN (6)
#define MAXLINE (100)

//pincrement: increment position counter for output
int pincrement(int pos, int num)
{
	if(pos + num < MAXLINE)
		return pos + num;
	else
		putchar('\n');

	return num;
}

int main(void)
{
	int c, pos;

	pos = 0; //position in the line
	while((c = getchar()) != EOF){
		if(iscntrl(c) || c == ' '){
			//non-graphic or blank
			if(c == '\n'){
				pos = 0;	//reset position for new line
				putchar('\n');
			}else{
				pos = pincrement(pos, OCTLEN);
				printf("\\%03o\n", c);
			}

		}else{ //graphic character
			pos = pincrement(pos, 1);

		}
	}

	return 0;
}
