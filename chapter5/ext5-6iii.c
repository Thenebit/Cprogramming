#include <stdio.h>
#include <ctype.h>

//atof: handling scientif notation
double atof (char *str)
{
	double val, power;
	int sign, exponent_sign, exponent;
	char *ptr = str;

	exponent_sign = 1;
	exponent = 0;

	//skip whitespace
	while(isspace(*ptr)){
		ptr++;
	}

	//finding sign number
	sign =  (*ptr == '-') ? -1 : 1;
	if (*ptr == '+' || *ptr == '-'){
		ptr++;
	}

	//convert the integer
	for(val = 0.0; isdigit(*ptr); ptr++) {
		val = 10.0 *  val + (*ptr - '0');
	}

	if (*ptr == '.'){	//convert the fraction
		ptr++;
	}
	for(power = 1.0; isdigit(*ptr); ptr++){
		val =  10.0 * val + (*ptr - '0');
		power *= 10.0;
	}

	//Handle scientific notation
    	if(*ptr == 'e' || *ptr == 'E') {
        	ptr++;
        	if (*ptr == '-') {
            		exponent_sign = -1;
            		ptr++;
        	}else if (*ptr == '+') {
            		ptr++;
        	}

        //Convert the exponent part
        	while (isdigit(*ptr)) {
            		exponent = 10 * exponent + (*ptr - '0');
            		ptr++;
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

