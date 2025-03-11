/*Exercise 3-5. Write the function itob(n,s,b) that converts the integer n
 into a base b character representation in the string s. In particular,
 itob(n,s, 16) formats n as a hexadecimal integer in s.
*/

#include <stdio.h>
#include <string.h>
#define MAX (100)

/*reverse: reverse string s in place*/
void reverse(char s[]);
/*itob: convert n to base representation*/
void itob(int n, char s[], int b);

int main()
{
	int n = 234;
	char s[MAX];
	//Where b is the base: 16
	itob(n, s, 16);
	printf("Base: %s\n", s);

	return 0;
}

void reverse(char s[])
{
	int i, c, j;

	j = strlen(s) - 1;

	for(i = 0; i < j; i++, j--){
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itob(int n, char s[], int b)
{
	int i, sign;
	char digits[] = "0123456789ABCDEFGHIJKLMNOPQRTUVXYZ";

	if((sign = n) < 0){ 	//record sign
		n = -n;		//make n positive
	}
	i = 0;
	do{
		s[i++] = digits[ n % b]; //finds the corresponding digits
	}while((n /= 10) > 0);
	if(sign < 0){
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s);
}
