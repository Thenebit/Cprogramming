/*A program to print the corresponding of Celsius to Fahrenheit on the table*/

#include <stdio.h>
#define LOW (0)
#define UPPER (300)
#define STEP (20)

int main()
{
	printf("Celsius\t\tFahrenheit\n");

	float fahr, celsius;

	for(fahr = LOW; fahr <= UPPER; fahr += STEP ){
		celsius = (5.0/9.0)*(fahr - 32.0);
		printf("%6.1f\t\t%3.0f\n" , celsius, fahr);
	}

	return 0;
}
