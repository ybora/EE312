// Printf_v1_Craig.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdint.h>

#define DEBUG true

// prints string value of x
void displayDecimal(int32_t x) {
	if (x == 0) { // special case for zero
		putchar('0');
		return; // 
	}

	if (x < 0) { // special case for negative
		putchar('-');
		x = -x;
		/* fall through and print abs value */
	}

	char digits[10];
	uint32_t num_digits = 0;

	while (x != 0) {
		int d = x % 10;
		char digit = d + '0';
		digits[num_digits] = digit;
		num_digits = num_digits + 1;
		x = x / 10;
	}

	while (num_digits > 0) {
		num_digits = num_digits - 1;
		putchar(digits[num_digits]);
	}
}

void displayString(char str[]) {
	uint32_t k = 0;
	while (str[k] != 0) {
		putchar(str[k]);
		k = k + 1;
	}
}


void MyPrintf(char fmt[], ...) {
	uint32_t k = 0;
	void* next_arg = &fmt + 1; // address of next argument (if there is a next)
	while (fmt[k] != 0) {
		if (fmt[k] == '%') {
			if (fmt[k + 1] == 'd') { // %d decimal
				int* p = (int*)next_arg;
				next_arg = p + 1;
				int x = *p;
				displayDecimal(x);
			}
			else if (fmt[k + 1] == 'c') { // %c character
				char* p = (char*)next_arg;
				next_arg = p + 1;
				char x = *p;
				putchar(x);
			}
			else if (fmt[k + 1] == 's') { // %s string
				char** p = (char**)next_arg;
				next_arg = p + 1;
				char* x = *p;
				displayString(x);
			}
			else if (fmt[k + 1] == 'f') { // %f floating point 
				double* p = (double*)next_arg;
				next_arg = p + 1;
				double x = *p;
				printf("%f", x);
			}
			else if (fmt[k + 1] == '%') { // %%
				putchar('%');
			}
			else { // WTH???
			}
			k += 2;
		}
		else {
			putchar(fmt[k]);
			k += 1;
		}
	}
}


int main(void) {
	int x = 42;
	int y = 65;
	MyPrintf("Hello World\n");

	MyPrintf("Hello %s, x is %c and y is %d, easy as %f\n",
		"EE312", 'A', y, 3.14159264);
}
