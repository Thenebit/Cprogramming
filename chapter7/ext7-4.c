/*Exercise 7-4. Write a private version of scanf analogous to minprintf from 
 the previous section.
*/

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

// minscanf: minimal scanf with variable argument list
int minscanf(char *fmt, ...)
{
	va_list ap;
	char *p;
	int *ival;
	unsigned *uval;
	double *dval;
	char *cval;
	char *sval;
	int count = 0;

	va_start(ap, fmt);


	for (p = fmt; *p; p++) {

		if (*p != '%') {
			continue; // Skip non-format characters
		}

		switch (*++p) {

		case 'd': // an integer
			ival = va_arg(ap, int *);
			if (scanf("%d", ival) == 1)
				count++;
			break;
		case 'u': // an unsigned integer
			uval = va_arg(ap, unsigned *);
			if (scanf("%u", uval) == 1)
				count++;
			break;
		case 'f': // a double
			dval = va_arg(ap, double *);
			if (scanf("%lf", dval) == 1)
				count++;
			break;
		case 'c': // a character
			cval = va_arg(ap, char *);
			if (scanf(" %c", cval) == 1)
				count++; // Space before %c skips whitespace
			break;
		case 's': // a string
			sval = va_arg(ap, char *);
			if (scanf("%s", sval) == 1)
				count++;
			break;
		default:
			break;
		}
	}

	va_end(ap);

	return count;
}

int main(void) 
{
	int i;
	unsigned u;
	double d;
	char c;
	char str[100];

	printf("enter an integer: ");
	minscanf("%d", &i);
	printf("You entered: %d\n", i);

	printf("enter an unsigned integer: ");
	minscanf("%u", &u);
	printf("You entered: %u\n", u);

	printf("enter a double: ");
	minscanf("%f", &d);
	printf("You entered: %f\n", d);

	printf("enter a character: ");
	minscanf("%c", &c);
	printf("You entered: %c\n", c);

	printf("enter a string: ");
	minscanf("%s", str);
	printf("You entered: %s\n", str);

	return 0;
}
