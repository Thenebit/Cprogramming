/*Exercise 4-4, Add commands to print the top element of the stack without
 popping, to duplicate it, and to swap the top two elements. Add a command
 to clear the stack.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXVAL (100)
#define MAXOP (100)
#define BUFSIZE (100)
#define NUMBER (0)

//getop: get next operator or numeric operand
int getop(char s[]){
    	int i = 0;
    	int c;

    //Skip whitespace
    	while ((s[0] = c = getch()) == ' ' || c == '\t');
    	s[1] = '\0'; //Null-terminate the string

    	if(!isdigit(c) && c != '.' && c !='-' && c != '+' && c !='p' && c != 'd'
		&& c != 's' && c != 'c'	){
        	return c; //Not a number
    	}

	//Handle negative numbers
    	if(c == '-' || c == '+'){
        	int next = getch();
        	if (isdigit(next) || next == '.') {
            		s[i++] = c;	//Store the sign
            		c = next; //Use the next character
        	}else{
            		ungetch(next); //Not a number, put it back
            		return c; //Return the sign
        	}
    	}

    //Collect integer part
    	if(isdigit(c)){
        	while(isdigit(s[++i] = c = getch()));
    	}

    //Collect fraction part
    	if (c == '.'){
        	s[i++] = c; //Add the decimal point
        	while(isdigit(s[i++] = c = getch()));
    	}
    	s[i] = '\0'; //Null-terminate the string

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

//getch: get a (possible pushed bacl) character
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

//print_pop: print the top value without popping
void print_top(void){
    	if(sp > 0){
        	printf("Top element: %.8g\n", val[sp - 1]);
    	}else{
        	printf("error: stack empty\n");
    	}
}

//duplicate: duplicate the top value
void duplicate(void){
    	if(sp > 0){
        	push(val[sp - 1]); //Duplicate the top element
    	}else{
        	printf("error: stack empty, can't duplicate\n");
    	}
}

//swap: swap the top two values
void swap(void){
   	 if(sp > 1){
        	double temp = val[sp - 1];
        	val[sp - 1] = val[sp - 2]; //Swap the top two elements
        	val[sp - 2] = temp;
    	}else{
        	printf("error: not enough elements to swap\n");
    	}
}

//clear: clear the stack 
void clear(void){
    	sp = 0; //Reset the stack pointer to clear the stack
    	printf("Stack cleared.\n");
}


int sp = 0;	//Stack pointer
double val[MAXVAL];	//Value stack
char buf[BUFSIZE];	//Buffer for ungetch
int bufp = 0;	//Buffer pointer

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
	    		case 'p':	//Print top element
                		print_top();
               			break;
            		case 'd':	//Duplicate top element
                		duplicate();
                		break;
            		case 's':	//Swap top two elements
                		swap();
               			break;
           	 	case 'c':	//Clear the stack
                		clear();
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


