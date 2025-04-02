/*Exercise 7-1. Write a program that converts uppercase to lowercase or 
 lowercase to uppercase, depending on the name it is invoked with, as 
 found in argv[0].
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

//change_tolower: converts input to lowercase
int change_tolower()
{
	int c;

	printf("change to lowercase: \n");
	while((c = getchar()) != EOF){
		putchar(tolower(c));
	}

	return 0;
}


// change_toupper: converts input to uppercase
int change_toupper()
{
	int c;

	printf("change to uppercase: \n\n");
	while ((c = getchar()) != EOF){
		putchar(toupper(c));
	}

	return 0;
}

int main(int argc, char *argv[])
{
	if(argc == 2){
		//checks if the name of the program contains the substring lower/upper
		if(strstr(argv[1], "lower") != NULL)
			change_tolower();
		else if(strstr(argv[1], "upper") != NULL)
			change_toupper();
		else
			printf("Error: Invalid program name. Use 'lower' or 'uper' \n");
	}else
		printf("Usage: ./name_of_compiled_file lower or ./name_of_compiled_file upper\n");

	//printf("Program name: %s\n", argv[0]);

	return 0;
}

