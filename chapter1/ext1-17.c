/* A program to print longest inputs greater than 80*/

#include <stdio.h>
#define MAXLINE (1000)
#define MINLINE (80)
#define MAXLINES (100)

/*get_line: calculate the longest input line*/
int get_line(char s[], int lim);
//void copy(char to[], char from[]);

int main()
{
	int len;
	int max;
	char line[MAXLINES][MAXLINE];
	char length[MAXLINES];

	max = 0;
	while(max < MAXLINES && (len = get_line(line[max], MAXLINE)) > 0){
		length[max] = len;
		max++;
	}

	printf("\nPRINTING ONLY LINES LONGER THAN 80\n");

	for(int i = 0; i < max; i++){
		if(length[i] >= MINLINE){
			printf("\nWord longer than 80 with %d characters: %s\n", length[i], line[i]);
		}
	}

	return 0;
}

int get_line(char s[], int lim)
{
	int c, i;
	for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i){
		s[i] = c;
	}
	if(c == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';

	return i;
}

/*
void copy(char to[], char from[])
{
	int i;

	i = 0;
	while((to[i] = from[i]) != '\0'){
		++i;
	}
}
*/
