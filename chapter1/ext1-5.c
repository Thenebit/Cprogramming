/*A program to print fahrenheit values in reverse from 300 to 0*/

#include <stdio.h>
#define LOW (0)
#define UPPER (300)
#define STEP (20)

int main()
{
	printf("Fahrenheit\tCelsius\n");

	float fahr;

	for(fahr = UPPER; fahr >= LOW; fahr -= STEP){
		printf("%3.0f\t\t%6.1f\n", fahr, (5.0/9.0)*(fahr -32.0));
	}

	return 0;
}
