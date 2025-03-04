/*Using fucntion to rewrite temperature conversion program*/

#include <stdio.h>
#define LOW (0)
#define UPPER (300)
#define STEP (20)

float conversion(float fahr)
{
	float celsius;

	celsius = (5.0/9.0) * (fahr - 32.0);
	return celsius;
}

int main()
{
	printf("Fahrenheit\tCelsius\n");
	float fahr;
	fahr = LOW;

	for(fahr = 0; fahr <= UPPER; fahr += STEP){
		printf("%3.0f\t\t%6.1f\n", fahr, conversion(fahr));
	}

	return 0;
}
