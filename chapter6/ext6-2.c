/*Exercise 6 - 2. Write a program that reads a c program and prints in
 alphabetical order each group of variable names that are identical in the
 first 6 characters, but different somewhere thereafter. Don't count words
 within strings and comments. make 6 a parameter that can be set from the
 commandline.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD (100) 	//max words
#define BUFSIZE (100)
#define VARLEN ((int) (sizeof vartype / sizeof vartype[0]))

char buf[BUFSIZE]; 	//buffer for ungetch
int bufp = 0; 	//next free position in buf

char *vartype[] = {
	"char",
	"const",
	"double",
	"enum",
	"extern",
	"float",
	"int",
	"long",
	"short",
	"signed",
	"static",
	"struct",
	"unsigned",
	"volatile"
};

struct tnode{
	char *word;
	int count;
	struct tnode *left; 	//left child
	struct tnode *right; 	//right child
};

//push character back on input
void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

//get a (possibly pushed back) character
int getch(void)
{
	if(bufp > 0)
		return buf[--bufp];

	return getchar();
}

//getword: get next word or character from input
int getword(char *word, int lim)
{
	int c;
	char *wrd = word;

	while(isspace(c = getch()));

	if(c != EOF)
		*wrd++ = c;
	if(!isalpha(c) && c != '_' && c != '*' && c != '&' && c != '='){
		if(c == '\"'){  //string constant
			for (; --lim > 0 && (c = getch()) != '\"' && c != EOF;)
				*wrd++ = c;
		}else if(c == '/'){   //comment
			if((c = getch()) == '/'){   //single line comment
				for (; --lim > 0 && (c = getch()) != '\n' && c != EOF;);
			}else if(c == '*'){   // mult-line comment
				for (; --lim > 0 && (c = getch()) != '*' && c != EOF;);
			}
		}else   //preprocessors and others
			for (; --lim > 0 && (c = getch()) != '\n' && c != EOF;);

		*wrd = '\0';

		return c;
        }

	if(c == '*' || c == '&'){	//accept names with * and &
		*wrd = '\0';

		return c;
	}

	for(; --lim > 0; wrd++){
		if(!isalnum(*wrd = getch()) && *wrd != '_'){
			ungetch(*wrd);
			break;
		}
	}

	*wrd = '\0';

	return word[0];
}

//binsearch: find word in tab[0]...tab[n-1]
int binsearch(char *word, char *tab[], int num)
{
	int i;

	for(i = 0; i < num ; i++){
		if(strcmp(word, tab[i]) == 0)
			return i;
	}

	return -1;
}

//talloc: make a tnode
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

//strdup: make a duplicate of s
char *_strdup(char *str)
{
	char *ptr;

	ptr = (char *) malloc(strlen(str) + 1); 

	if(ptr != NULL)
		strcpy(ptr, str);

	return ptr;
}

//addtree: add a node with w, at or below p
struct tnode *addtree(struct tnode *ptr, char *wrd)
{
	int cond;

	if(ptr == NULL){ //a new word has arrived
		ptr = talloc(); //make a new node
		ptr -> word = _strdup(wrd);
		ptr -> count = 1;
		ptr -> left = ptr -> right = NULL;
	}else if((cond = strcmp(wrd, ptr -> word)) == 0)
		ptr -> count++; //repeated word
	else if(cond < 0) //less than into left subtree
		ptr -> left = addtree(ptr -> left, wrd);
	else //greater than into right subtree
		ptr -> right = addtree(ptr -> right, wrd);

	return ptr;
}

//strncmp: compare first n characters if str_1 and str_2
int _strncmp(char *str_1, char *str_2, int num)
{
	int i;

	for(i = 1; i < num && (*str_1 == *str_2) 
		&& *str_1 != '\0'; i++, str_1++, str_2++);

	if((i == num) && *str_1 != '\0'){
		while(*str_1 != '\0'){
			if(*str_1++ != *str_2++)
				//the remaining characters are different
				return 1;
                }
        }

	return -1; 
}

//treeprint: in-order print tree p
void treeprint(struct tnode *ptr, int check)
{
	static int prev = 1; //print previous node
	static struct tnode *previous;

	if(ptr != NULL){
		treeprint(ptr -> left, check);

		if(check == 0)
			printf("%4d %s\n", ptr -> count, ptr -> word);
		else{
			if(previous != NULL){
				if(_strncmp(previous->word, ptr->word, 
					check)){
					if(prev){
						printf("%4d %s\n",
							previous->count, 
							previous->word);
						prev = 0; //reset print previous
                                        }
					printf("%4d %s\n", ptr->count,	
						ptr->word);
				}else
					prev = 1; //set print previous
			}
				previous = ptr; //track current node encountered
		}
		treeprint(ptr -> right, check);
	}
}


int main(int argc, char *argv[])
{
	int check = 0;
	struct tnode *root;
	char word[MAXWORD];


	if(argc - 1 > 0){
		if(isdigit(*argv[1]))
			check = atoi(argv[1]);
		else{
			printf("error: invalid command\n");
			printf("enter a number eg. ./varsort 6\n");
			return -1;
		}
	}else
		check = 0;

	root = NULL;

	while(getword(word, MAXWORD) != EOF){
		if(isalpha(word[0]) || word[0] == '_'){
			//add to tree if not a keyword or type
			if(binsearch(word, vartype, VARLEN) < 0) 
				root = addtree(root, word);
		}
	}

	printf("\n");
	treeprint(root, check);

	return 0;
}
