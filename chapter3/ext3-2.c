/*Exercise 3-2. Write function escape(s,t) that converts characters like 
 newline and tab into visible escape sequences like \n and \t as it copies
 the string t to s. Use a switch. Write a function for the other direction 
 as well, converting escape sequences into the real characters.
*/

#include <stdio.h>
#define MAXLINES (1000)

/*escape: convert escape character to real characters*/
void escape(char s[], char t[]);
/*undo_escape: convert ecape characters back to escape sequence*/
void undo_escape(char s[], char t[]);

int main()
{
	char s[MAXLINES];
	char t[MAXLINES];
	char n[MAXLINES];
	int i;

	i = 0;
	printf("Type: ");

	while((t[i] = getchar()) != EOF && i < MAXLINES){
		i++;
	}
	t[i] = '\0';

	escape(s, t);
	printf("\nConverted escape characters: %s", s);

	undo_escape(s, n);
	printf("\nReconverted to actual escape sequnece: %s\n", n);

	return 0;
}

void escape(char s[], char t[])
{
	int i, j;

	i = j = 0;

	while(t[i]){
		switch(t[i]){
			case '\n':
				s[j++] = '\\';
				s[j++] = 'n';
				break;
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;
			default:
				s[j++] = t[i];
		}
		i++;
	}
	s[j] = '\0';
}

void undo_escape(char s[], char t[])
{
	int i , j;

	i = j = 0;

	while(s[i]){
	//Using nestd switch instead of using if, else to achive result
		switch(s[i]){
			case '\\':	//Check for backspace
				switch(s[++i]){
					case 'n':
						t[j++] = '\n';
						break;
					case 't':
						t[j++] = '\t';
						break;
					default:
						t[j++] = s[i];
						break;
				}
				break;
			default:
			t[j++] = s[i];
			break;
		}

		i++;
	}
	t[j] = '\0';
}
