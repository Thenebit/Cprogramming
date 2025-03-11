/*Exercise 2-3. Write the function htoi (a), which converts a string of hexa-decimal digits (including an optional Ox or OX) into its equivalent integer value
The allowable digits are 0 through 9, a through f, and A through F.*/

#include <stdio.h>

/*htoi: convert string to hexidecimal value*/
int htoi(char s[])
{
	int i, n;

	i = 0;
	n = 0;

	//Verify if the string is indeed a hex
	if(s[i] == '0' && (s[i+ 1 ] == 'x' || s[i + 1] == 'X')){
		i += 2;		//shift two steps if 0x, 0X exists
	}

	for(; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f')
		|| (s[i] >= 'A' && s[i] <= 'F'); ++i){
		n *= 16;

		if(s[i] >= '0' && s[i] <= '9'){
			n += s[i] - '0';
		}else if(s[i] >= 'a' && s[i] <= 'f'){
			n += s[i] - 'a' + 10;
		}else if(s[i] >= 'A' && s[i] <= 'F'){
			n += s[i] - 'A' + 10;
		}
	}
	return n;
}

int main()
{
	char hexnumbers[] = "0x15B3";
	int equivalentnum = htoi(hexnumbers);

	printf("Hexadecimal number \"%s\" to integer %d\n", hexnumbers, equivalentnum);

	return 0;
}
