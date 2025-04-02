/*Exercise 6-5. Implement a simple version of the #define processor (i.e, no 
 arguments) suitable for use with c programs, based on the routines of this 
 section. you may also find getch and ungetch helpful.
 push character back on input
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD (100) 
#define BUFSIZE (100)
#define HASHSIZE (101)
#define TABLE_SIZE (10)

enum {FALSE, TRUE};
int valid = FALSE;
int getDef = FALSE;

//table entry
struct nlist{ 
        struct nlist *next; //next entry in chain
        char *name; //defined name
        char *defn; //replacement text;
};

static struct nlist *hashtab[HASHSIZE]; //pointer table

char buf[BUFSIZE]; //buffer for ungetch
int bufp = 0; //next free position in buf

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

        while (isspace(c = getch()));

        if(c != EOF)
                *wrd++ = c;
        if(!isalnum(c) && c != '#' && c != '(' && c != '\'' && c != '\"'){
                *wrd = '\0';
                return c;
        }

        if(!valid){ //check if #define preprocessor
                if(c == '#'){
                        for(; --lim > 0; wrd++){
                                //getting #define
                                if(!isalpha(*wrd = getch()) 
                                        && *wrd != '#'){
                                        *wrd = '\0';
                                        break;
                                }
                        }
                        *wrd = '\0';

                        if(strcmp(word, "#define") == 0){
                                //set valid to true
                                valid = TRUE;
                                return word[0];
                        }
                }
        }

        //if valid, get name
        if(valid && !getDef){
                if(!isalpha(c) && c != '_'){
                        *wrd = '\0';
                        valid = FALSE; // reset for next def
                        return c;
                }

                //get name
                for(; --lim > 0; wrd++){
                        //getting #define
                        if(!isalpha(*wrd = getch()) && *wrd != '_'){
                                ungetch(*wrd);
                                break;
                        }
                }
                *wrd = '\0';

                getDef = TRUE;
                return word[0];
        }

        //if getDef, get definition
        if(getDef){

                if(!isalnum(c) && c != '(' && c != '\'' && c != '\"'){
                        *wrd = '\0';
                        valid = FALSE; // reset for next def
                        getDef = FALSE;
                        return c;
                }

                if(c == '('){//def in brackets
                        if((c = *wrd++ = getch()) == '\''){//char def
                                if(isalnum(*wrd++ = getch()) 
                                        && (*wrd++ = getch()) == '\'' 
                                        && (*wrd++ = getch()) == ')'){
                                        *wrd = '\0';
                                        valid = FALSE; // reset for next def
                                        return word[0];
                                }else{
                                        valid = FALSE; // reset for next def
                                        getDef = FALSE;
                                }
                        }else if(c == '\"'){//string def
                                //get string
                                for(; --lim > 0; wrd++){
                                        //getting #define
                                        if(!isalnum(*wrd = getch()) 
                                                && *wrd != '\"'){
                                                ungetch(*wrd);
                                                break;
                                        }
                                }
                                *wrd = '\0';

                                if(*(wrd - 1) != '\"'){
                                        valid = FALSE; // reset for next def
                                        getDef = FALSE;
                                }else{
                                        if((*wrd++ = getch()) == ')'){
                                                valid = FALSE; // reset
                                                return word[0];
                                        }else{
                                                // reset for next def
                                                valid = FALSE; 
                                                getDef = FALSE;
                                        }
                                }
                        }else if(isdigit(c)){//number def
                                //get number
                                for(; --lim > 0; wrd++){
                                        //getting #define
                                        if(!isdigit(*wrd = getch()) 
                                                && *wrd != ')'){
                                                ungetch(*wrd);
                                                break;
                                        }
                                }
                                *wrd = '\0';

                                if(*(wrd - 1) != ')'){
                                        valid = FALSE; // reset for next def
                                        getDef = FALSE;
                                }else{
                                        valid = FALSE; // reset for next de
                                        return word[0];
                                }
                        }else{
                                valid = FALSE; // reset for next def
                                getDef = FALSE;
                        }
                }else if(c == '\''){//char def
                        if(isalnum(*wrd++ = getch()) 
                                && (*wrd++ = getch()) == '\''){
                                *wrd = '\0';
                                valid = FALSE; // reset for next de
                                return word[0];
                        }else{
                                valid = FALSE; // reset for next def
                                getDef = FALSE;
                        }
                }else if(c == '\"'){//string def
                        //get string
                        for(; --lim > 0; wrd++){
                                //getting #define
                                if(!isalnum(*wrd = getch()) 
                                        && *wrd != '\"'){
                                         ungetch(*wrd);
                                        break;
                                }
                        }
                        *wrd = '\0';

                        if(*(wrd - 1) != '\"'){
                                valid = FALSE; // reset for next def
                                getDef = FALSE;
                        }else{
                                valid = FALSE; // reset for next de
                                return word[0];
                        }
                }else{//number def
                        if(isdigit(c)){
                                //get number
                                for(; --lim > 0; wrd++){
                                        //getting #define
                                        if(!isdigit(*wrd = getch())){
                                                ungetch(*wrd);
                                                break;
                                        }
                                }
                                *wrd = '\0';
                                valid = FALSE; // reset for next de
                                return word[0];
                        }else{
                                valid = FALSE; // reset for next def
                                getDef = FALSE;
                        }
                }
        }

        *wrd = '\0';
        return c; //invalid word
}

//hash: form hash value for string str
unsigned hash(char *str)
{
        unsigned hashval;

        for(hashval = 0; *str != '\0'; str++)
                hashval = *str + 31 * hashval;

        return hashval % HASHSIZE;
}

//strdup: make a duplicate of str
char *_strdup(char *str)
{
        char *ptr;

        ptr = (char *) malloc(strlen(str) + 1); //+1 for '\0'

        if(ptr != NULL)
                strcpy(ptr, str);
 
        return ptr;
}

//lookup: look for str in hashtab
struct nlist *lookup(char *str)
{
        struct nlist *nptr;

        for(nptr = hashtab[hash(str)]; nptr != NULL; nptr = nptr -> next){
                if(strcmp(str, nptr -> name) == 0)
                        return nptr; //found
        }

        return NULL; //not found
}

//install: put (name, defn) in hashtab
struct nlist *install(char *name, char *defn)
{
        struct nlist *nptr;
        unsigned hashval;

        if((nptr = lookup(name)) == NULL){//not found
                nptr = (struct nlist *) malloc(sizeof(*nptr));

                if(nptr == NULL || (nptr -> name = _strdup(name)) == NULL)
                        return NULL;

                hashval = hash(name);
                nptr -> next = hashtab[hashval];
                hashtab[hashval] = nptr;
        }else //already there
                free((void *) nptr -> defn); //free previous defn

        if((nptr -> defn = _strdup(defn)) == NULL)
                return NULL;

        return nptr;
}

//undef: remove (name, defn) from hashtab
struct nlist *undef(char *name)
{
        struct nlist *nptr;

        if((nptr = lookup(name)) != NULL){//found
                if(nptr -> next != NULL){//check if next is assigned
                        //move the other tree nodes up
                        nptr -> next = nptr -> next -> next;

                        //replace current (nptr) with next
                        nptr = nptr -> next;
                }else{ //if next is null
                        hashtab[hash(name)] = NULL;
                        free((void *) nptr); //free *nptr
                }
        }

        return NULL; //not found or already removed
}

int main(void)
{
        int i, j;
        char word[MAXWORD];
        char name[MAXWORD];
        char def[MAXWORD];
        static struct nlist *table[TABLE_SIZE];

        j = 0;
        while(getword(word, MAXWORD) != EOF){
                i = 0;
                if(valid){//if valid get name
                        while(word[i] != '\0'){
                                name[i] = word[i];
                                i++;
                        }
                        name[i] = '\0';

                }else if(getDef){ //if getdef is true
                        while(word[i] != '\0'){ //get definition
                                def[i] = word[i];
                                i++;
                        }
                        def[i] = '\0';

                        //printf("name: %s and def: %s\n", name, def);

                        // add name and def to table
                        table[j++] = install(name, def);
                        getDef = FALSE;
                }
        }

        printf("\n");
        //print table contents
        for(i = 0; i < TABLE_SIZE && table[i] != NULL; i++)
                printf("%s -> %s \n", table[i] -> name, table[i] -> defn);

        return 0;
}
