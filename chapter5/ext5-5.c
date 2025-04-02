/**Write versions of the library functions strncpy. strcat, and strncmp,
 which operate on at most the first n characters of their argument strings.
 For example, strncpy(s, t, n) copies at most n characters of t to s. Full
 descriptions are in Appendix B.
*/

#include <stdio.h>

#define MAX (500)

//strncpy: copy t to s
char strncopy(char *str, const char *t_str, int num)
{
	char *strp = str;		//double pointer to save destination pointer

	for(int i = 0; i < num; i++){
		if(*t_str == '\0'){
			break;		//break when end of t reaches
		}
		//continue copying characters till i = n, and t reaches '\0'
		*str++ = *t_str++;
	}

	return *strp;
}

//strnconcat: copy t to end of s
char strnconcat(char *str, const char *t_str, int num)
{
	char strp;

	while(*str++ != '\0');

	str--;		//remove \0
	strp = strncopy(str, t_str, num);

	return strp;
}

//strcmp: return (< 0) if (s < t), (0) if (s == t), or (> 0) if (s > t)
int strcmpare(const char *strp, const char *t_strp, int num)
{
	int i;
	const char *str = strp;
	const char *strr = t_strp;

	for(i = 0; i < num; i++){
		//compare characters and return difference
		if(*strp != *t_strp){
			return *str - *strr;
		}

		//check if string reached end
		if(*strp == '\0'){
			return 0;
		}

		//move to next character
		strp++;
		t_strp++;
	}

	//strings up to n characters and equal
	return 0;
}

int main()
{
	int num = 15;
	char strr[MAX];
	char *duplicate = "@silzeus, ready to be deployed!";

	//strncopy
	strncopy(strr, duplicate, num);
	printf("%s\n", strr);

	//strnconcat
	char str[MAX] = "zedulo, ";
	strnconcat(str, duplicate, num);
	printf("%s\n", str);

	//strcmpare
	num = 8;
	char str2[MAX] = "@silzeus";
        int result = strcmpare(str2, duplicate, num);

	if(result == 0)
        	printf("it is equal to: %d\n", result);
	else if(result > 0)
		printf("it is greater than: %d\n", result);
	else
		printf("it is less than: %d\n", result);

	return 0;
}

