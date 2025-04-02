/*Exercise 6 - 2. Write a cross_referencer that prints a list of all words in a
 document, and, for each word, a list of the line numbers on which it occurs.
 Remove noise words like "the", "and", and so on.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD (100)
#define BUFSIZE (100)
#define SIZE(word) ((int) (sizeof word / sizeof word[0]))
#define MAXLINE (100) //for line array size
#define NMAX (20)

char buf[BUFSIZE]; //buffer for ungetch
int bufp = 0; //next free position in buf

//struct of all noise words
struct noise_words{
	char begins_with;
	char *word[NMAX];
};

struct noise_words words[] = {
    { 'a', {"a", "about", "after", "all", "also", "an", "and", "another","any", 
                "are", "as", "at", NULL} },
    { 'b', {"be", "because", "been", "before", "being", "between", "both", 
                "but", "by", NULL} },
    { 'c', {"came", "can", "come", "could", NULL}},
    { 'd', {"did", "do", NULL}},
    { 'e', {"each", "even", NULL}},
    { 'f', {"for", "from", "further", "furthermore", NULL}},
    { 'g', {"get", "go", NULL}},
    { 'h', {"had", "has", "have", "he", "her", "here", "hi", "him", "himself", 
                "his", "how", "however", NULL}},
    { 'i', {"i", "if", "in", "indeed", "into", "is", "it", "its", NULL}},
    { 'j', {"just", NULL}},
    { 'l', {"like", NULL}},
    { 'm', {"made", "many", "me", "might", "more", "moreover", "most", "much", 
                "must", "my", NULL}},
    { 'n', {"never", "not", "now", NULL}},
    { 'o', {"of", "on", "only", "or", "other", "our", "out", "over", NULL}},
    { 's', {"said", "same", "see", "she", "should", "since", "some", "still", 
                "such", NULL}},
    { 't', {"take", "than", "that", "the", "their", "them", "then", "there",
                "therefore", "these", "they", "this", "those", "through",
                "thus", "to", "too", NULL}},
    { 'u', {"under", "up", NULL}},
    { 'v', {"very", NULL}},
    { 'w', {"was", "way", "we", "well", "were", "what", "when", "where", 
                "which", "while", "who", "will", "with", "would", NULL}},
    { 'y', {"you", "your", NULL}},
    { '\0', {NULL} } // null terminator for the array
};// no k, p, q, r, x, z noise words

//tree to store every other word
struct tnode{//the tree node:
	char *word; //points to the text
	int line[MAXLINE]; //every line word occurs
	int index; //to track the current line index
	struct tnode *left; //left child
	struct tnode *right; //right child
};

//to_lowercase: make all words lowercase
char *to_lowercase(char str[])
{
	int i;

	for(i = 0; str[i] != '\0'; i++) 
		str[i] = tolower(str[i]);

	return str;
}

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

int getword(char *word, int lim, int *line)
{
        int c;
        char *wrd = word;

        // skip whitespace, but don't skip newlines
        while(isspace(c = getch())){
                if(c == '\n')
                        (*line)++; //new line detected
        }

        if(c != EOF)
                *wrd++ = c;
        if(!isalpha(c)){
                *wrd = '\0';
                return c;
        }

        for(; --lim > 0; wrd++){
                //accept words with dashes and apostrophes
                if(!isalnum(*wrd = getch()) && *wrd != '-' 
                        &&  *wrd != '\''){
                        ungetch(*wrd);
                        break;
                }
        }

        *wrd = '\0';

        return word[0];
}

//binsearch: find word in tab[0]...tab[n-1]
int binsearch(char *word, struct noise_words check[])
{
        int i;
        //char *lower_word;

        // no k, p, q, r, x, z noise words
        if(word[0] != 'k' && word[0] != 'p' && word[0] != 'q' && word[0] 
                != 'r' && word[0] != 'x' && word[0] != 'z'){

                while((check->begins_with) != '\0'){
                        if(check->begins_with == tolower(word[0]))
                                break;
                        check++;
                }

                for(i = 0; check->word[i] != NULL ; i++){
                        if(strcmp(to_lowercase(word), check->word[i]) == 0)
                                return i;
                }
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

        ptr = (char *) malloc(strlen(str) + 1); //+1 for '\0'

        if(ptr != NULL)
                strcpy(ptr, str);
        
        return ptr;
}

//addtree: add a node with w, at or below p
struct tnode *addtree(struct tnode *ptr, char *wrd, int line)
{
        int cond, len, newline = 1;

        if(ptr == NULL){ //a new word has arrived
                ptr = talloc(); //make a new node
                ptr -> word = _strdup(wrd);
                ptr -> index = 0;
                ptr -> line[ptr -> index++] = line;
                ptr -> left = ptr -> right = NULL;
        }else if((cond = strcmp(wrd, ptr -> word)) == 0){ //repeating word
                //check if it's on a new line
                int j;
                len = (ptr -> index) + 1;

                for(j = 0; j < len; j++){
                        if(ptr -> line[j] == line){
                                newline = 0; //found on the same line
                                break;
                        }            
                }

                if(newline)
                        ptr -> line[ptr -> index++] = line; //found on a new line
        }
        else if(cond < 0) //less than into left subtree
                ptr -> left = addtree(ptr -> left, wrd, line);
        else //greater than into right subtree
                ptr -> right = addtree(ptr -> right, wrd, line);
        
        return ptr;
}

//treeprint: in-order print tree p
void treeprint(struct tnode *ptr)
{
        int i, len;

        if(ptr != NULL){
                len = SIZE(ptr -> line);

                treeprint(ptr -> left);

                printf("Word: %s \noccurs on lines: ", ptr -> word);
                for(i = 0; i < len && (ptr -> line[i]) != 0; i++)
                        printf("%d ", ptr -> line[i]);
                printf("\n\n");

                treeprint(ptr -> right);
        }
}

//word frequency count
int main(void)
{
        struct tnode *root;
        char word[MAXWORD];
        int line = 1;

        root = NULL;

        while(getword(word, MAXWORD, &line) != EOF){
                if(isalpha(word[0])){
                        //add to tree if not a noise word
                        if(binsearch(word, words) < 0)
                                root = addtree(root, word, line);
                }
        }

        printf("\n");
        treeprint(root);

        return 0;
}
