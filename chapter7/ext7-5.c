/*Exercise 7-5. Rewrite the postfix calculator of chapter 4 to use scanf and /or sscanf to do the input and number conversion.
*/

#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>

#define MAX_OP (100)  //max size of operator
#define NUMBER ('0')  //a number is found
#define BUFSIZE (100)   //buffer size
#define MAX_VAL (100)

char buf[BUFSIZE];
int bufp = 0;

int sp = 0;
double val[MAX_VAL];

void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int getch(void)
{
	char c;

	if(bufp > 0)
		return buf[--bufp];
	else
		scanf("%c", &c);

	return c;
}

int getop(char *str)
{
	int i, c;

	while((str[0] = c = getch()) == ' ' || c == '\t');  //skip whitespace

	str[1] = '\0';

	i = 0;
	if(!isdigit(c) && c != '.' && c != '-')
		return c; // not a number

	if(c == '-'){   //negative number
		if(isdigit(c = getch()) || c == '.')
			str[++i] = c;
		else{
			if(c != EOF)
				ungetch(c);
			return '-';
		}
	}

	if(isdigit(c))  //collect integer part
		while(isdigit(str[++i] = c = getch()));

	if(c == '.')  //collect fractional part
		while (isdigit(str[++i] = c = getch()));

	str[i] = '\0';

	if(c != EOF)
		ungetch(c);

	return NUMBER;
}

void push(double num)
{
	if (sp < MAX_VAL)
		val[sp++] = num;
	else
		printf("error: stack full, can't push %g\n", num);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else
		printf("error: empty stack\n");

	return -1;
}

//reverse polish calculator
int main(void)
{
	int type;
	double op2;
	char str[MAX_OP];

	while((type = getop(str)) != EOF){
		switch(type){
			case NUMBER:
				push(atof(str));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if(op2 > 0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: invalid or unknown command\n");
				break;
		}
	}

	return 0;
}
