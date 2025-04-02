#include <stdio.h>
#include <string.h>
#include <limits.h>
#define LENGTH (12)

/*reserse: revese string s*/
void reverse(char *str)
{
	char *start = str;
	char *end = str + strlen(str) - 1;
	char c;

	while(end > start){
		c = *start;
		*start = *end;
		*end-- = c;
	}
}

/*itoa: itoa to help handle negative numbers that are large*/
void itoa(int num, char *str)
{
	int sign;
	char *ptr = str;

	//special case to handle huge negative number
	if(num == INT_MIN){	//Largest negative value from limits.h
		*ptr++ = '2';
		num = 147483648;	//a postive vale that can be handled
		sign = 1;
	}else{
		sign = (num < 0) ? -1 : 1;   //Determine thew sign and set n to postive
		num = (num < 0) ? -num : num;
	}

	do{
		*ptr++ = n % 10 + '0';
	}while((num /= 10) > 0);

	if(sign < 0){
		*ptr++ = '-';
	}
	*ptr = '\0';

	reverse(str);
}

int main()
{
	int digit;
	char str[LENGTH];

	//Large negative number
	digit = INT_MIN;
	itoa(digit, str);
	printf("Largest negative number: %d to %s\n", digit, str);

	//Test postive values
	digit = 12345;
	itoa(digit, str);
	printf("Postive number: %d to %s\n", digit, str);

	return 0;
}
