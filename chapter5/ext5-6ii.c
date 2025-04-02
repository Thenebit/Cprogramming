#include <stdio.h>
#define MAXLINE (1000)

//getline: get line into s, return length
int get_line(char *str, int lim)
{
	int c, i;

	i = 0;
	while(lim > 0 && (c = getchar()) != EOF && c != '\n'){
		*str++ = c;
	}

	if(c == '\n'){
		*str++ = c;
		++i;
	}
	*str = '\0';

	return i;
}

//strrindex: return the position of t in s
int strrindex(char *str, char *t_str)
{
	int i;
	int lastindex = -1;	//set to negative to indicate not found

	for(i = 0; *str++ != '\0'; i++){
		//check if t maches s[i]
		//k = i;

		char *s_ptr = &str[i];
		char *t_ptr = t_str;

		while( *t_ptr != '\0' && *s_ptr !='\0' && *s_ptr == *t_ptr){
			s_ptr++;
			t_ptr++;
		}

		if(*t_ptr++ == '\0'){
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
