/* Exercise 7-3. Revise minprintf to handle more of the other facilities of
  printf.
*/

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

// Minprintf - a minimal printf function
int minprintf(char *fmt, ...) {
	va_list ap;
	char *p, *sval;
	int ival;
	double dval;
	unsigned uval;
	int cval;

	va_start(ap, fmt); // initialize the argument pointer


	for (p = fmt; *p; p++) {
		if (*p != '%') { // If the character is not '%', just print
			putchar(*p);
			continue;
		}

		switch (*++p) {
		case 'd':	// expect an integer.
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;
		case 'u': // expect an unsigned integer.
			uval = va_arg(ap, unsigned);
			printf("%u", uval);
			break;
		case 'f': // expect a double
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 'c': // expect a character
			cval = va_arg(ap, int);
			putchar(cval);
			break;
		case 's': // expect a string
			for (sval = va_arg(ap, char *); *sval; sval++)
				putchar(*sval);
			break;
		default: // just print any other character
			putchar(*p);
			break;
		}
	}


	va_end(ap);

	return 0;
}

int main(int argc, char *argv[])
{

	minprintf("This is a test of minprintf\n");
	minprintf("This is a test of minprintf with an integer: %d\n", 50);
	minprintf("This is a test of minprintf with an unsigned integer: %u\n", 42);
	minprintf("This is a test of minprintf with a double: %f\n", 50.0);
	minprintf("This is a test of minprintf with a character: %c\n", 'S');
	minprintf("This is a test of minprintf with a string: %s\n", "Hello, World!");

	return 0;
}
