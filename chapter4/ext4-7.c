/*Exercise 4-8. Suppose that there will never be more than one character of
 pushback. Modify getch and ungetch accordingly.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXVAL (100)
#define MAXOP (100)
#define NUMBER (0)

//getop: get next operator or numeric operand
int getop(char s[]){
	int i = 0;
	int c;

    //Skip whitespace
	while((s[0] = c = getch()) == ' ' || c == '\t');
    	s[1] = '\0';	//Null-terminate the string

    	if(!isdigit(c) && c != '.'){
        	return c;	//Not a number
    	}
	i = 0;
    //Collect integer part
    	if (isdigit(c)){
        	while (isdigit(s[++i] = c = getch()));
    	}

    //Collect fraction part
    	if (c == '.'){
        	s[i++] = c;	//Add the decimal point
        	while (isdigit(s[i++] = c = getch()));
    	}
    	s[i] = '\0';	//Null-terminate the string

    	if (c != EOF){
        	ungetch(c);
    	}
    	return NUMBER;
}

//push: push f onto value stack
void push(double f){
	if (sp < MAXVAL){
        	val[sp++] = f;
    	}else{
        	printf("error: stack full, can't push %g\n", f);
    	}
}

//pop: pop and return top value from stack
double pop(void){
	if (sp > 0){
        	return val[--sp];
    	}else{
        	printf("error: stack empty\n");
        	return 0.0;
    	}
}

//getch: get a (possible pushed bacl) character
int getch(void){
	int temp = lastch;	//get the push character
	lastch = EOF;	//reset to indicate no character
	return (temp != EOF) ? temp : getchar();
}

//push character back on input
void ungetch(int c){
    	if (lastch != EOF){
        	printf("ungetch: too many characters\n");
    	}else{
        lastch = c;
    }
}

int sp = 0;	//Stack pointer
double val[MAXVAL];	//Value stack
int lastch = 0;		//pushback character, lastch means last character


int main() {
	int type;
    	double op2;
    	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
                		push(atof(s));
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
                		if (op2 != 0.0) {
                    			push(pop() / op2);
                		}else{
                    			printf("error: zero divisor\n");
                		}
                		break;
	    		case '%':
				op2 = pop();
				if(op2 != 0.0){
					push((int)pop() % (int)op2);
				}else{
					printf("error: zero divisor in modulus\n");
				}
				break;
	   		case '\n':
                		printf("\t%.8g\n", pop());
                		break;
            		default:
	        		printf("error: unknown command %s\n", s);
                		break;
		}
	}
    return 0;
}
