/*Exercise 2-4, Write an alternate version of squeeze(s1,s2) 
that deletes each character in s1 that matches any character in string s2
*/

#include <stdio.h>

/*squeeze: deleting each charater in s1 matching in s2*/
void squeeze(char s1[], char s2[])
{
	int i, j, k;
	int found;

	for(i = j = 0; s1[i] != '\0'; i++){
		found = 0;
		for(k = 0; s2[k] != '\0'; k++){
			if(s1[i] == s2[k]){
				found = 1;
			}
		}
		if(!found){
			s1[j++] = s1[i];
		}
	}
	s1[j] = '\0';
}

int main()
{
	char original[] = "zedulo";
	char chartodel[] = "zlgkv";

	printf("Actual string: \"%s\" \n", original);

	squeeze(original, chartodel);

	printf("Removed \"%s\" from actual string and got this  \"%s\" \n", chartodel, original);

	return 0;
}
