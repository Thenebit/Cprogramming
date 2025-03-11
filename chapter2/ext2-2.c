
/*Exercise 2-2. write a loop equivalent to the for loop above without using
 && or ||
*/

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
	int c, i, length;

	length = lim - 1;
	for(i = 0; i < length; ++i){	//used if in place of && and ||
		c = getchar();
		if(c == EOF){
			break;
		}
		if(c == '\n'){
			break;
		}
		s[i] = c;
	}
	if(c == '\n'){
		if(i < length){
			s[i] = c;
			++i;
		}
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
