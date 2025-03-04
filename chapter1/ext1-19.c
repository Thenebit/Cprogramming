/*A program to preint the reverse of inputs for each line*/

#include <stdio.h>
#define MAXLINE (1000)

int get_line(char s[], int length);
//void copy(char to[], char from[]);
void reverse(char s[]);

int main()
{
	int len;
	char line[MAXLINE];

	while((len = get_line(line, MAXLINE)) > 0){
		if(len > 0 && line[len - 1] == '\n'){
			line[len - 1] = '\0';
			len--;
		}
		reverse(line);
		printf("\nReversed line: %s\n", line);
	}

	return 0;
}

int get_line(char s[], int length)
{
	int c, i;

	for(i = 0; i < length - 1 && (c = getchar()) != EOF && c != '\n'; ++i){
		s[i] = c;
	}
	if(s[i] == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';

	return i;
}

void reverse(char s[])
{
	int strlength;

	strlength = 0;
	while(s[strlength] != '\0'){
		strlength++;
	}

	for(int i = 0; i < strlength /2; i++){
		char mirage_mem = s[i];
		s[i] = s[strlength - i - 1];
		s[strlength -i -1] = mirage_mem;
	}
}
