/* Exercise 7-8. Write a program to print a set of files, starting each new //
 one on a new page, with a title and a running page count for each file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE (1000) // maximum input line length

int main(int argc, char *argv[])
{
	FILE *fp;	     // file pointer
	char line[MAXLINE];  // input line
	int line_number = 0; // line number
	char *pattern;	     // pattern to search for
	int page_count = 1;

	// check for correct number of arguments
	if(argc < 2){
		fprintf(stderr, "Usage: %s pattern [file1 file2 ...]\n", argv[0]);

		exit(EXIT_FAILURE);
        }
	pattern = argv[1];

	if(argc == 2){
		fp = stdin;
		printf("File: Styandard Input\n");
	}else{
		// read from named files
		for(int i = 2; i < argc; i++){
			if((fp = fopen(argv[i], "r")) == NULL){
				fprintf(stderr, "Can't open %s\n", argv[i]);

				exit(EXIT_FAILURE);
			}

			printf("\fFile: %s (Page %d)\n", argv[i], page_count);
			page_count++;

			line_number = 0;	//reset line number

			// compare files line by line
			while(fgets(line, MAXLINE, fp) != NULL){
				line_number++;

				if(strstr(line, pattern) != NULL){
					//if(argc > 3)
						//printf("%s: ", argv[i]);

					printf("line %d: %s", line_number, line);
				}
			}

			fclose(fp);
		}
	}

	return 0;
}
