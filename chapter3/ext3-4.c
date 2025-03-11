/*Exercise 3-4. In a two's complement number representation, our version of
 itoa does not handle the largest negative number, that is, the value of n
 equal to -(2^(wordsize-1)). Explain why not. Modify it to print that value
 correctly regardless of the machine on which it runs.
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>
#define LENGTH (12)

/*reserse: revese string s*/
void reverse(char s[]);

/*itoa: itoa to help handle negative numbers that are large*/
void itoa(int n, char s[]);

int main()
{
	int digit;
	char s[LENGTH];

	//Large negative number
	digit = INT_MIN;
	itoa(digit, s);
	printf("Largest negative number: %d to %s\n", digit, s);

	//Test postive values
	digit = 12345;
	itoa(digit, s);
	printf("Postive number: %d to %s\n", digit, s);

	return 0;
}

void itoa(int n, char s[])
{
	int i, sign;

	i = 0;

	//special case to handle huge negative number
	if(n == INT_MIN){	//Largest negative value from limits.h
		s[i++] = '2';
		n = 147483648;	//a postive vale that can be handled
		sign = 1;
	}else{
		sign = (n < 0) ? -1 : 1;   //Determine thew sign and set n to postive
		n = (n < 0) ? -n : n;
	}

	do{
		s[i++] = n % 10 + '0';
	}while((n /= 10) > 0);
	if(sign < 0){
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s);
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
