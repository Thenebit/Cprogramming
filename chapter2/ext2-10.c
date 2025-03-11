/*Exercise 2-10, Rewrite the function Lower, which converts upper case 
letters to lower case, with a conditional expression instead of if-else.
*/

#include <stdio.h>

/*lowercae: converts uppercase to lowcase character*/
char lowercase(char c)
{
	return (c >= 'A' && c <= 'Z') ? (c + 32) : c;
}

int main()
{
	char letter = 'Z';
	char convertToUpper = lowercase(letter);

	printf("Converted uppercase letter '%c' to lowercase '%c'\n", letter, convertToUpper);

	return 0;
}
