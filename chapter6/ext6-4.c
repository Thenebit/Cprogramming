/*Excercise 6 - 2. Write a program that prints the distinct words in its input 
 sorted into decreasing order of frequency of occurrence. Precede each word by 
 its count.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD (100) //max # words
#define BUFSIZE (100)
#define ORDER_SIZE (1000) //max order array size

char buf[BUFSIZE]; //buffer for ungetch
int bufp = 0; //next free position in buf

//tree node
struct tnode{
        char *word;   //points to the text
        int count;  //number of occurrences
        struct tnode *left;   //left child
        struct tnode *right;  //right child
};

struct words{
        char *word;
        struct words *nextword;
};

struct ordernode{
        int number;
        struct words *wordlist;
        struct ordernode *left;
        struct ordernode *right;
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

int getword(char *word, int lim)
{
        int c;
        char *wrd = word;

        while (isspace(c = getch()));

        if(c != EOF)
                *wrd++ = c;
        if(!isalpha(c)){
                *wrd = '\0';
                return c;
        }

        for(; --lim > 0; wrd++){
                if(!isalnum(*wrd = getch()) && *wrd != '-' 
                        &&  *wrd != '\''){
                        ungetch(*wrd);
                        break;
                }
        }

        *wrd = '\0';

        return word[0];
}

//talloc: make a tnode
struct tnode *talloc(void)
{
        return (struct tnode *) malloc(sizeof(struct tnode));
}

//make an ordernode
struct ordernode *ordernode_alloc(void) 
{
    return (struct ordernode *) malloc(sizeof(struct ordernode));
};

//word_alloc: make a word node
struct words *words_alloc(void) 
{
    return (struct words *) malloc(sizeof(struct words));
};


//strdup: make a duplicate of s
char *_strdup(char *str)
{
        char *ptr;

        ptr = (char *) malloc(strlen(str) + 1); //+1 for '\0'

        if(ptr != NULL)
                strcpy(ptr, str);

        return ptr;
}

//addtree: add a node with word, at or below ptr
struct tnode *addtree(struct tnode *ptr, char *wrd)
{
        int cond;

        if(ptr == NULL){ //a new word has arrived
                ptr = talloc(); //make a new node
                ptr -> word = _strdup(wrd);
                ptr -> count = 1;
                ptr -> left = ptr -> right = NULL;
        }else if((cond = strcmp(wrd, ptr -> word)) == 0){
                ptr -> count++; //repeated word
        }
        else if(cond < 0) //less than into left subtree
                ptr -> left = addtree(ptr -> left, wrd);
        else //greater than into right subtree
                ptr -> right = addtree(ptr -> right, wrd);

        return ptr;
}

//addwordtolist: add new word to word list
struct words *addwordtolist(struct words *list, char *wrd) 
{
        if(list == NULL){
                list = words_alloc();
                list -> word = _strdup(wrd);
                list -> nextword = NULL;
        }else
                list -> nextword = addwordtolist(list -> nextword, wrd);

        return list;
}

//addordertree: add a node with word, at or below ptr
struct ordernode *addordertree(struct ordernode *ptr, int num, char *wrd) 
{
        if(ptr == NULL){
                ptr = ordernode_alloc();
                ptr -> number = num;
                ptr -> wordlist = NULL;
                ptr -> wordlist = addwordtolist(ptr -> wordlist, wrd);
        }else if(ptr -> number == num)
                addwordtolist(ptr -> wordlist, wrd);
        else if(ptr -> number < num)
                ptr -> left = addordertree(ptr -> left, num, wrd);
        else
                ptr -> right = addordertree(ptr -> right, num, wrd);

        return ptr;
}

//printwords: print words in list
void printwords(const struct words *wrd, const int count) 
{
        if(wrd != NULL){
                printf("%d -> %s", count, wrd -> word);
                wrd = wrd -> nextword;
        }

        while(wrd != NULL){
                printf(", %s", wrd -> word);
                wrd = wrd -> nextword;
        }
        printf("\n");
}

//traverse: look through ordernode to arrange words
struct ordernode *traverse(const struct tnode *ptr, struct ordernode *order) 
{
        if(ptr != NULL){
                order = traverse(ptr -> left, order);
                order = addordertree(order, ptr -> count, ptr -> word);
                order = traverse(ptr -> right, order);
        }

        return order;
}

//treeprint: in-order print ordernode p
void treeprint(struct ordernode *ptr)
{
        if(ptr != NULL){
                treeprint(ptr -> left);
                printwords(ptr -> wordlist, ptr -> number);
                treeprint(ptr -> right);
        }
}

//word frequency count
int main(void)
{
        struct tnode *root;
        struct ordernode *order_root;
        char word[MAXWORD];

        root = NULL;
        order_root = NULL;

        while(getword(word, MAXWORD) != EOF){
                if(isalpha(word[0]))
                        root = addtree(root, word);
        }

        order_root = traverse(root, order_root);

        printf("\n");
        treeprint(order_root);

        return 0;
}
