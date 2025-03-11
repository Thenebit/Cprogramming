/*Exercise 2-5. Write the function any(s1,s2), which returns the first
location in the string s1 where any character from the string s2 occurs,
or -1 if s1 contains no characters from s2. (The standard library function
strpbrk does the same job but returns a pointer to the location.)
*/

#include <stdio.h>
#include <string.h>

/*any: return thew location of first string in s1 that is in s2*/
void any(const char *s1, const char *s2)
{
	const char *location = strpbrk(s1, s2);

	if(location != NULL){
		printf("first character in \"%s\" found in \"%s\": '%c'\n", s2, s1, *location);
		printf("the location was %ld in \"%s\"\n", location - s1, s1);
	}else{
		printf("-1\n");
	}
}

int main()
{
	const char *s1 = "ghdu";
	const char *s2 = "kqwb";

	any(s1, s2);

	return 0;
}
