/*A program to print the frequencies of diff characters in its input*/

#include <stdio.h>
#define ASCII_MAX (256)

int main()
{
	int c;
	int ascii_freq[ASCII_MAX] = {0};

	while((c = getchar()) != EOF){
		++ascii_freq[c];
	}

	printf("\nFrequencies of characters in inputs\n");

	for(int i = 0; i < ASCII_MAX; ++i){
		if(ascii_freq[i] > 0){
			printf("'%c' --> %d\n", i, ascii_freq[i]);
		}
	}

	return 0;
}
