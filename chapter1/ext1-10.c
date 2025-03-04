/*A program to replace tabs with (\t), backspace with (\b), backlash with (\\)*/

#include <stdio.h>
#define TAB '\t'
#define BACKSPACE '\b'
#define BACKSLASH '\\'

int main()
{

	int c;
	int escape_seq = '\t';
	int escape_seq2 = '\b';
	int escape_seq3 = '\\';

	while((c = getchar()) != EOF){
		if(c == TAB){
			if(escape_seq != TAB){
				putchar('\\');
				putchar('t');
			}
		}else if(c == BACKSPACE){
			if(escape_seq2 != BACKSPACE){
				putchar('\\');
				putchar('b');
			}	/*Backspace issue*/
		}else if(c == BACKSLASH){
			if(escape_seq3 != BACKSLASH){
				putchar('\\');
				putchar('\\');
			}	/*Backspace issue*/
		}else{
			putchar(c);
		}
		escape_seq = c;
		escape_seq2 = c;
		escape_seq3 = c;
	}

	return 0;
}
