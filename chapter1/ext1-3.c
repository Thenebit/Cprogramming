/*A program for temperature conversion align with their headings*/

#include <stdio.h>
#define LOW (0)
#define UPPER (300)
#define STEP (20)

int main()
{
	printf("Fahrenheit\tCelsius\n");

	float fahr, celsius;

	fahr = LOW;
	while(fahr <= UPPER){
		celsius = (5.0/9.0)*(fahr-32.0);
		printf("%3.0f\t\t%6.1f\n", fahr, celsius);
		fahr = fahr + STEP;
	}

	return 0;
}
