/*Exercise 5-3. Write a pointer version of the function strcat that we
 showed in Chapter 2: strcat(s,t) copies the string t to the end of s.
*/

#include <stdio.h>
#include <string.h>

#define MAX (50)

//str_cat: concate t to end of s; s must be big enough
void str_cat(char *str, const char *t_str)
{
	while(*str != '\0'){	//find end of s
		str++;
	}

	while((*str++ = *t_str++) != '\0');	//copy t
}

int main()
{
	char str[MAX] = "developer @";
	char t_str[MAX] = " zedulo";

	str_cat(str, t_str);
	printf("%s\n", str);

	return 0;
}
