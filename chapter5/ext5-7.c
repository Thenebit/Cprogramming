/**Exercise 5-7. Rewrite readlines to store lines in an array supplied by
 main, rather than calling alloc to maintain storage. How much faster is
 the program?
*/ 

#include <stdio.h>
#include <string.h>

#define MAXLINES (5000)
#define MAX_LENGTH (1000)
#define MAXSTORAGE (10000)

char *lineptr[MAXLINES];
char linestore[MAXSTORAGE];

//__getline: get length of string
int __getline(char *str, int lim) {
        int c, i;

        for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
                str[i] = c;
        if (c == '\n')
                str[i++] = c;
        str[i] = '\0';

        return (i);
}

//readlines: read inputs lines
int readlines(char *lineptr[], int maxlines, char *buffer) {

        int len, nlines = 0;
        char *pointer = buffer;
        char line[MAX_LENGTH];

        while ((len = __getline(line, MAX_LENGTH)) > 0) {
                if (nlines >= maxlines || (buffer + MAXSTORAGE - pointer < len))
                        return -1;
                else {
                        line[len - 1] = '\0'; /* delete newline */
                        strcpy(pointer, line);
                        lineptr[nlines++] = pointer;
                }
        }

        return (nlines);
}

//writelines: write output lines
int writelines(char *lineptr[], int nlines) {
        while (nlines-- > 0)
                printf("%s\n", *lineptr++);

        return 0;
}

//qsort: sort v[left]..v[right] into increasing order
int qsort(char *v[], int left, int right) {
        int i, last;

        int swap(char *v[], int i, int j);
        if (left >= right)/*do nothing if array contains less than 2 elements */
                return 0;

        swap(v, left, (left + right) / 2);
        last = left;

        for (i = left + 1; i <= right; i++) {
                if (strcmp(v[i], v[left]) < 0)
                        swap(v, ++last, i);
        }

        swap(v, left, last);
        qsort(v, left, last - 1);
        qsort(v, last + 1, right);

        return 0;
}

//swap: interchange v[i] and v[j]
int swap(char *v[], int i, int j) {
        char *temp = v[i];
        v[i] = v[j];
        v[j] = temp;

        return 0;
}

int main(void)
{
        int nlines; /* number of input lines read */

        if ((nlines = readlines(lineptr, MAXLINES, linestore)) >= 0) {
                qsort(lineptr, 0, nlines - 1);
                writelines(lineptr, nlines);
                return 0;
        } else {
                printf("error: input too big to sort\n");
                return 1;
        }

        return 0;
}
