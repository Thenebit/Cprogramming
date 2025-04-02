/*Exercise 5-4, Write the function strend(s,t), which returns 1 if the
 string t occurs at the end of the string s, and zero otherwise,
*/

#include <stdio.h>
#include <string.h>

#define MAX (50)

//strend: concate t to end of s; s must be big enough
int strend(const char *str, const char *t_str)
{
	int len_s = strlen(str);
	int len_t = strlen(t_str);

	if(len_t > len_s){	//cannot be at end if t is longer
		return 0;
	}

	str += len_s - len_t;	//move pointer to compare substrings

	return strcmp(str, t_str) == 0;
}

int main()
{
	char *str = "hello, Zedulo";
	char *t_str = "Zedulo";
	char *t1_str = "samuel";

	int str_end;

	str_end = strend(str, t_str);
	printf("Does '%s' end with '%s' ? %d\n", str, t_str,  str_end);

	str_end = strend(str, t1_str);
	printf("Does '%s' end with '%s' ? %d\n", str, t1_str,  str_end);

	return 0;
}
