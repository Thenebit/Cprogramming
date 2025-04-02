/*Exercise 5-1. As written, getint treats a + or
 - not followed by a digit as a
 valid representation of zero. Fix it to push such a character back on the input.
*/

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE (100)

char buf[BUFSIZE];
int bufp = 0;

//ungetch: push a character back into the input buffer
void ungetch(int c)
{
	if(bufp >= BUFSIZE){
		printf("ungetch: too many characters\n");
	}else{
		buf[bufp++] = c;
	}
}

//getch: reads a character from the input buffer
int getch(void)
{
	if(bufp > 0){
		return buf[--bufp];
	}else{
		return getchar();
	}
}

//getint: get next integer from input into *pn
int getint(int *pn)
{
	int c, sign;

	while(isspace(c = getchar()));	//skip whitespace

	if(!isdigit(c) && c != EOF && c != '+' && c != '-'){
		ungetch(c);	//it's not a number
		return 0;
	}

	//sign = (c == '-') ? -1 : 1;
	if(c == '-'){
		sign  = -1;
	}else{
		sign = 1;
	}

	if(c == '+' || c == '-'){
		c = getch();
	}

	for(*pn = 0; isdigit(c); c = getch()){
		*pn = 10 * *pn + (c - '0');
	}

	if(*pn == 0 && c != '0'){
		ungetch(sign == 1 ? '+' : '-');
		return 0;
	}

	*pn *= sign;
	if(c != EOF){
		ungetch(c);
	}

	return c;
}

int main()
{
	int i, arr[BUFSIZE], getint(int *);

        for(i = 0; i < BUFSIZE && getint(&arr[i]) != EOF; i++);

	printf("\n");

        printf("%d\n", arr[0]);

	return 0;
}
