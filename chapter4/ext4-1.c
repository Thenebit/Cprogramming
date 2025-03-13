/*Exercise 4-1, Write the function strrindex(s,t), which returns the position
 of the rightmost occurrence of t in s, or -1 if there is none.
*/

#include <stdio.h>
#define MAXLINE (1000)

//getline: get line into s, return length
int get_line(char *s, int lim)
{
	int c, i;

	i = 0;
	while(lim > 0 && (c = getchar()) != EOF && c != '\n'){
		*s++ = c;
	}

	if(c == '\n'){
		*s++ = c;
		++i;
	}
	*s = '\0';

	return i;
}

//strrindex: return the position of t in s
int strrindex(char s[], char t[])
{
	int i, j, k;
	int lastindex = -1;	//set to negative to indicate not found

	for(i = 0; s[i] != '\0'; i++){
		//check if t maches s[i]
		k = i;

		for(j = 0; t[k] != '\0' && s[j] !='\0' && s[j] == t[k]; j++, k++);

		if(t[k] == '\0'){
			lastindex = i;	//update lastindex position
		}
	}
	return lastindex;
}

int main()
{

	char pattern[] = "ould";
	char line[MAXLINE];
	int found = 0;

	while(get_line(line, MAXLINE) > 0){
		int index = strrindex(line, pattern);
		if(index >= 0){
			printf("found position at %d for %s\n", index, line);
			found++;
		}
	}
	return found;

	return 0;
}

