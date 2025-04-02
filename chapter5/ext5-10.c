//Exercise 5-14. Modify the sort program to handle a -r flag, which indicates 
//sorting in reverse (decreasing) order. Be sure that -r works with -n

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES (5000)		//max #lines to be sorted
#define ALLOCSIZE (10000) 	//size of available space

static char allocbuf[ALLOCSIZE]; 	//storage for alloc
static char *allocp = allocbuf; 	//next free position

char *lineptr[MAXLINES]; 	//pointers to text lines

//return pointer to n characters
char *alloc(int num)
{
        if((allocbuf + ALLOCSIZE - allocp) >= num){
                allocp += num;
                return allocp - num;
        }else
                return 0;
}

//getline: read a line into s, return length
int _getline(char *line, int lim)
{
        int c;
        char *p = line;

        while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
                *line++ = c;

        if(c == '\n')
                *line++ = c;
        *line = '\0';

        return line - p;
}

//readline: read input lines
int readlines(char *lineptr[], int maxlines)
{
        int len, nlines;
        char *p, line[MAXLINES];

        nlines = 0;
        while((len = _getline(line, MAXLINES)) > 0){
                if(nlines >= maxlines || (p = alloc(len)) == NULL)
                        return -1;
                else{
                        line[len - 1] = '\0'; 		//remove newline
                        strcpy(p, line);
                        lineptr[nlines++] = p;
                }
        }

        return nlines;
}

//writelines: write output lines
void writelines(char *lineptr[], int nlines, int order)
{
        int i;

        i = 0;
        if(order){
                for(i = nlines - 1; i >= 0; i--)
                        printf("%s\n", lineptr[i]);
        }else{
                for(i = 0; i < nlines; i++)
                        printf("%s\n", lineptr[i]);
        }
}

//swap
void swap(void *v[], int i, int j)
{
        void *temp;

        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
}

//numcmp: compare s1 and s2 numerically
int numcmp(const char *str1, const char *str2)
{
        double line1, line2;;

        line1 = atof(str1);
        line2 = atof(str2);

        if(line1 < line2)
                return -1;
        else if(line1 > line2)
                return 1;

        return 0;
}

//qsort: sort v[left]...v[right] into increasing order
void _qsort(void *lines[], int left, int right, int (*comp)(void *, void *))
{
        int i, last;

        if(left >= right)
                return;

        swap(lines, left, (left + right)/2);
        last = left;

   	for(i = left + 1; i <= right; i++){
                if((*comp)(lines[i], lines[left]) < 0)
                        swap(lines, ++last, i);
        }

        swap(lines, left, last); 	//restore partition element
        _qsort(lines, left, last - 1, comp);
        _qsort(lines, last + 1, right, comp);
}

//sort input lines
int main(int argc, char *argv[])
{
        int i;
        int nlines; //number of input lines read
        int numeric = 0; //1 if numeric sort
        int reverse = 0; //1 if sorting in reverse order

        for(i = 1; i < argc; i++){
                if(strcmp(argv[i], "-n") == 0)
                        numeric = 1;
                else if(strcmp(argv[i], "-r") == 0)
                        reverse = 1;
                else if(strcmp(argv[i], "-h") == 0){
                        printf("usage: sort -n -r\n(where adding each command is optional)\n");
                        printf("-n : numeric sorting\n-r: reverse sorting order\n");
                        return -1;
                }else{
                        printf("error: invalid or unknown command; type sort -h for help\n");
                        return -1;
                }
        }

        if((nlines = readlines(lineptr, MAXLINES)) >= 0){
                printf("\n");
                _qsort((void **) lineptr, 0, nlines - 1,
                        (int (*)(void *, void *)) (numeric ? numcmp : strcmp));
                writelines(lineptr, nlines, reverse);
        }else{
                printf("input too big to sort\n");
                return 1;
        }

        return 0;
}
