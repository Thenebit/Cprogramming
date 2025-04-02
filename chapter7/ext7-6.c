/* Exercise 7-6. Write a program to compare two files, printing the first line
 where they differ.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE (1000)  //maximum input line length

int main(int argc, char *argv[])
{

	FILE *fp1, *fp2;		     // file pointers
	char line1[MAXLINE], line2[MAXLINE]; // input lines
	int line_number = 0;		     // line number


	// check for correct number of arguments
	if(argc != 3){
		fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
		exit(EXIT_FAILURE); // exit with failure status
        }
	// open file 1
	if((fp1 = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "Can't open %s\n", argv[1]);
		exit(EXIT_FAILURE);
        }
	// open file 2
	if((fp2 = fopen(argv[2], "r")) == NULL){
		fprintf(stderr, "Can't open %s\n", argv[2]);
		exit(EXIT_FAILURE);
        }
	// compare files line by line
	while(fgets(line1, MAXLINE, fp1) != NULL && fgets(line2, MAXLINE, fp2) != NULL){

		line_number++;

		if(strcmp(line1, line2) != 0){
			printf("Files differ at line %d:\n", line_number);
			printf("%s: %s", argv[1], line1);
			printf("%s: %s", argv[2], line2);

			break;
		}
	}



	fclose(fp1);
	fclose(fp2);

	return 0;
}
