/*Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations
 like a-z in the string s1 into the equivalent complete list abc..xyz in s2. 
 Allow for letters of either case and digits, and be prepared to handle cases
 like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken
 literally.
*/

#include <stdio.h>
#define MAXLEN (200)

/*expand: expands shorthand notations into the equivalent complete list*/
void expand(char s1[], char s2[]);

int main()
{
	char s1[] = "a-z0-9";
	char s2[MAXLEN];

	expand(s1, s2);
	printf("Expanded notation: %s\n", s2);

	return 0;
}

void expand(char s1[], char s2[])
{
	int i , j;

	i = j = 0;

	while(s1[i] != '\0'){
		switch(s1[i]){
			case '-':
				if(i == 0 && s1[i + 1] == '\0'){
					s2[j++] = s1[i]; //check, add hypen
				}else{
					//Check charater before and after dash
					char before = s1[i - 1];
					char after = s1[i+ 1];
					//Check if character is with range and add it
					if(before < after){
						for(char character = before + 1; character <= after; character++){
							s2[j++] = character;
						}
					}
					i++;
				}

				break;
			default:
				s2[j++] = s1[i];
			break;
		}
		i++;
	}
	s2[j] = '\0';
}
