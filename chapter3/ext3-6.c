/*Exercise 3-6. Write a version of itoa that accepts three arguments instead
 of two. The third argument is a minimum field width; the converted number
 must be padded with blanks on the left if necessary to make it wide enough.
*/

#include <stdio.h>
#include <string.h>
#define MAX (100)

/*itoa: */
void itoa(int n, char s[], int width);

/*reverse: reverse string in order*/
void reverse(char s[]);

int main()
{
	int n = 234;
	char s[MAX];

	itoa(n, s, 10);
	printf("%s\n", s);

	return 0;
}

void itoa(int n, char s[], int width)
{
	int i, sign;
	char digits[] = "0123456789";

	if((sign = n) < 0){
		n = -n;
	}
	i = 0;

	do{
	 	s[i++] = digits[n % 10];
	} while((n /= 10) > 0);
	if(sign < 0){
		s[i++] = '-';
	}
	s[i] = '\0';
	 // Reverse the string to get the correct order
	reverse(s);

	//Padding with blanks
	int padding = width - i;
	if(padding > 0){
		for(int j = i + padding; j >= padding; j--){	//Shift right to make padding
			s[j] = s[j - padding];
		}
		for(int j = 0; j < padding; j++){ 	//replace padding areas with blanks
			s[j] = ' ';
		}
		s[i + padding] = '\0';
	}
}

void reverse(char s[])
{
	int c, i, j;

	j = strlen(s) - 1;

	for(i = 0; i < j; i++, j--){
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
