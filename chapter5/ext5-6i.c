#include <stdio.h>

#define MAXLINE (1000)

//getline: read a line into s, return length
int my_getline(char *str, int lim)
{
	int i, c, length;

	length = lim - 1;

	for(i = 0; i < length && (c = getchar()) != EOF && c != '\n'; ++i){
		*str++ = c;
	}
	if(c == '\n'){
		*str++ = c;
		++i;
	}

	*str = '\0';

	return i;
}

//copy: copy characters in from to to
void copy(char to[], char from[])
{
	int i;

	i = 0;
	while((to[i] = from[i]) != '\0'){
		++i;
	}
}

int main()
{
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];

	max = 0;

	while((len = my_getline(line, MAXLINE)) > 0){
		if(len > max){
			max = len;
			copy(longest, line);
		}
	}

	if(max > 0){
		printf("\nLongest word is %d characters: %s\n", max, longest);
	}

	return 0;
}
