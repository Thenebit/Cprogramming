/*Exercise 4-3. Given the basic framework, it’s straightforward to extend the calculator. Add the modulus (x) operator and provisions for negative
 numbers
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXVAL (100)
#define MAXOP (100)
#define BUFSIZE (100)
#define NUMBER (0)

int sp = 0;	//Stack pointer
double val[MAXVAL];	//Value stack
char buf[BUFSIZE];	//Buffer for ungetch
int bufp = 0;	//Buffer pointer

//getop: get next operator or numeric operand
int getop(char s[]){
    	int i = 0;
    	int c;

    //Skip whitespace
    	while ((s[0] = c = getch()) == ' ' || c == '\t');
   	s[1] = '\0';	//Null-terminate the string

    	if(!isdigit(c) && c != '.'){
        	return c;	//Not a number
    	}

    //Collect integer part
    	if(isdigit(c)){
        	while(isdigit(s[++i] = c = getch()));
    	}

    //Collect fraction part
    	if(c == '.'){
        	s[i++] = c;	//Add the decimal point
        	while(isdigit(s[i++] = c = getch()));
    	}
    	s[i] = '\0';	/*Null-terminate the string*/

    	if(c != EOF){
        	ungetch(c);
    	}
    	return NUMBER;
}

//push: push f onto value stack
void push(double f){
    	if(sp < MAXVAL){
       	 	val[sp++] = f;
    	}else{
        	printf("error: stack full, can't push %g\n", f);
    	}
}

//pop: pop and return top value from stack
double pop(void){
    	if(sp > 0){
        	return val[--sp];
    	}else{
        	printf("error: stack empty\n");
        	return 0.0;
    	}
}

//getch: get a (possible pushed back) character
int getch(void){
    	if (bufp > 0) {
        	bufp = bufp - 1; 	//Decrement bufp
    		return buf[bufp]; 	//Return the character at the new bufp index
	}else{
    		return getchar(); 	//Read and return a character from standard input
	}

}

//push character back on input
void ungetch(int c){
    	if(bufp >= BUFSIZE){
        	printf("ungetch: too many characters\n");
    	}else{
        	buf[bufp++] = c;
    	}
}

int main() {
    	int type;
    	double op2;
    	char s[MAXOP];

    	while((type = getop(s)) != EOF){
        	switch(type){
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
                		if(op2 != 0.0){
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


