/*Exercise 5-2. Write getfloat, the floating-point analog of getint.
 What type does get float return as its function value?
*/
#include <stdio.h>
#include <ctype.h>

#define BUFSIZE (100)

char buf[BUFSIZE];
int bufp = 0;

//getch: reads a character from the input buffer
int getch(void)
{
        if(bufp > 0)
		return buf[--bufp];

	return getchar();
}

//ungetch: push a character back into the input buffer
void ungetch(int c)
{
	if(bufp >= BUFSIZE){
		printf("ungetch: too many characters\n");
	}else{
		buf[bufp++] = c;
	}
}

//getint: get next float from input into *pn
int getfloat(float *pn)
{
	int c, sign;
	float power;

	while(isspace(c = getch()));	//skip whitespace
  
	if(!isdigit(c) && c!= EOF && c != '+' && c != '-' && c != '.'){
		ungetch(c);	//it's not a number
		return 0;
	}

	//sign = (c == '-') ? -1 : 1;
	if(c == '-')
	        sign = -1;
	else
	        sign = 1;

	if(c == '+' || c == '-'){
		c = getch();
	}

	//collect integer part
	for(*pn = 0; isdigit(c); c = getch()){
		*pn = 10 * *pn + (c - '0');
	}

	//collect decimal part
	if(c == '.'){
		c = getch();

		for(power = 1.0; isdigit(c); c = getch()){
			*pn = 10 * *pn + (c - '0');
			power *= 10;
		}
	}else
		power = 1.0;	//no decimal part, set power to 1


	*pn *= sign / power;	//apply sign and scale by power
	if(c != EOF){
		ungetch(c);
	}

	return c;
}

int main()
{
	float number;
	int result;


	printf("Enter number:\n");
	while((result = getfloat(&number)) !=EOF){
		if(result){
			printf("float entered: %.2f\n", number);
		}else{
			printf("Not a valid float\n");
		}
	}

	return 0;
}
