/*Exercise 4-2. Extend atof to handle scientific notation of the form
 123.45e-6
 where a floating-point number may be followed by e or E and an optionally
 signed exponent.
*/

#include <stdio.h>
#include <ctype.h>

//atof: handling scientif notation
double atof (char s[])
{
	double val, power;
	int i, sign, exponent_sign, exponent;

	exponent_sign = 1;
	exponent = 0;

	//skip whitespace
	for(i = 0; isspace(s[i]); i++);
	//finding sign number
	sign =  (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-'){
		i++;
	}

	//convert the integer
	for(val = 0.0; isdigit(s[i]); i++) {
		val = 10.0 *  val + (s[i] - '0');
	}

	if (s[i] == '.'){	//convert the fraction
		i++;
	}
	for(power = 1.0; isdigit(s[i]); i++){
		val =  10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	//Handle scientific notation
    	if (s[i] == 'e' || s[i] == 'E') {
        	i++;
        	if (s[i] == '-') {
            		exponent_sign = -1;
            		i++;
        	}else if (s[i] == '+') {
            		i++;
        	}

        //Convert the exponent part
        	while (isdigit(s[i])) {
            		exponent = 10 * exponent + (s[i] - '0');
            		i++;
        	}
        	exponent *= exponent_sign; //Apply the sign to the exponent
	}

	// Adjust the value based on the exponent
   	 while (exponent > 0) {
        	val *= 10.0;
        	exponent--;
    	}
    	while (exponent < 0) {
        	val /= 10.0;
        	exponent++;
    	}

    	return sign * val / power;
}

int main()
{
	char str1[] = "123.45e-6";
	char str2[] = "1.23E+3";
	char str3[] = "-456.78e2";

    	printf("String %s to fraction  %f\n", str1, atof(str1));
    	printf("String %s to fraction  %f\n", str2, atof(str2));
    	printf("String %s to fraction  %f\n", str3, atof(str3));

    	return 0;
}

