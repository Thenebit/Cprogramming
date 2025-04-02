/*Exercise 6-1. our version of getword does not properly handle underscores,
 string constants, comments, or preprocessor control lines. write a better
 version.
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define NKEYS ((int)(sizeof keytab / sizeof keytab[0]))
#define MAXWORD (100)
#define BUFSIZE (100)

char buf[BUFSIZE]; 	//buffer for ungetch
int bufp = 0;	   	//next free position in buf

//keywords
struct key {
	char *word;
	int count;
};

struct key keytab[] = {
   { "auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

//push character back on input
void ungetch(int c) {
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

//get a (possibly pushed back) character
int getch(void) {
	if(bufp > 0)
		return buf[--bufp];

	return getchar();
}

//getword: get next word or character from input
int getword(char *word, int lim) {
	int c;
	char *wrd = word;

	while (isspace(c = getch()));

	if (c != EOF)
		*wrd++ = c;

	switch (c) {
        	case '\"': // Handle string constants
            	while (--lim > 0 && (c = getch()) != '\"' && c != EOF)
                	*wrd++ = c;

            	if(c == '\"')
                	*wrd++ = c; // include the closing quote

            	*wrd = '\0';

            	return word[0];

		break;
        case '/': // Handle comments
            if((c = getch()) == '/') { // single-line comment
                while ((c = getch()) != '\n' && c != EOF);
                *wrd = '\0';
                return word[0];
            }else if(c == '*'){ // multi-line comment
                while(1){
                    c = getch();
                    if (c == EOF) break;
                    if (c == '*') {
                        if ((c = getch()) == '/') break; // end of comment
                    }
                }
                *wrd = '\0';

                return word[0];
            }else{
                ungetch(c); // not a comment, push back
            }

            break;
        case '#': // Handle preprocessor directives
            while (--lim > 0 && (c = getch()) != '\n' && c != EOF) {
                *wrd++ = c;
            }
            *wrd = '\0';

            return word[0];
	    break;
        default: // Handle identifiers (including underscores)
            if (isalpha(c) || c == '_') {
                for (; --lim > 0; wrd++) {
                    if (!isalnum(*wrd = getch()) && *wrd != '_') {
                        ungetch(*wrd);
                        break;
                    }
                }
                *wrd = '\0';
                return word[0];
            }
            break;
    }

    *wrd = '\0'; // Not a valid word

    return c;    // Return the character read

}

// binsearch: find word in tab[0]...tab[n-1]
int binsearch(char *word, struct key tab[], int num) {
	int cond;
	int low, mid, high;

	low = 0;
	high = num - 1;
	while (low <= high) {
		mid = (low + high) / 2;

		if((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}

	return -1;
}

// count c keywords
int main(void) {
	int num;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0])) {
			if ((num = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[num].count++;
		}
	}

	printf("\n");
	for (num = 0; num < NKEYS; num++) {
		if (keytab[num].count > 0)
			printf("%4d %s\n", keytab[num].count, keytab[num].word);
	}

	return 0;
}

