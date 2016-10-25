// printf_from_Sum16.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma GCC diagnostic ignored "-Wwrite-strings"
#include <stdint.h>
#include <stdio.h>
void printf_v1(char fmt[]) {
	char a = 'a';
	char b = 'b';
	char c = 'c';
	int32_t l = 0;
	int32_t m = 0;
	int32_t n = 0;
	int32_t *p = &l;
	int32_t o = 0;
	int arr[] = { 1, 2, 3 };

	printf("%p %p %p\n", (void*)&a, (void *)&b, (void *)&c); // 12 bytes apart -- 4 for pointer, and 4 for data
	printf("%p %p %p %p %p\n", (void*)&l, (void *)&m, (void *)&n, &p, &o);

	printf("%p %p %p\n", (void *)&(arr[0]), (void *)&(arr[1]), (void *)&(arr[2]));
	uint32_t k = 0;
	while (fmt[k] != 0) {
		putchar(fmt[k]);
		k += 1;
	}
}

void printf_v2(char* fmt, uint32_t a) {
	uint32_t* p = &a;
	printf("%p %p\n", (void *)&fmt, (void *)p);
}

void displayString(char str[]) {
	uint32_t k = 0;
	while (str[k] != 0) {
		putchar(str[k]);
		k += 1;
	}
}

// Only for strings
void printf_v3(char* fmt, ...) {
	uint32_t k = 0;
	char** p = &fmt + 1; // pointer to the argument after fmt (the string to be printed)
	while (fmt[k] != 0) { // print non-format stuff that is part of format string
		if (fmt[k] != '%') {
			putchar(fmt[k]);
			k += 1;
		}
		else { // fmt[k] is the beginning of an escape sequence, e.g., %s
			   /* I'm just going to assume %s for now */
			char* x = *p;
			displayString(x);
			k = k + 2; // we add 2 to skip the % and the s, and then resume our loop.
		}
		// k = k + 2; // we add 2 to skip the % and the s, and then resume our loop.
	}
}

void displayDecimal(int32_t x) {
	if (x == 0) { // special case for zero
		putchar('0');
		return; // GTFO
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

void printf_v4(char fmt[], ...) { // print decimal
	int* p = (int*)(&fmt + 1); // argument after 1
	int x = *p;
	displayDecimal(x);
}

// Print character
void printf_v5(char fmt[], ...) {
	int * p = (int*)(&fmt + 1);
	char x = *p;
	putchar(x);
}

// Print double
void printf_v6(char fmt[], ...) {
	double* p = (double*)(&fmt + 1);
	printf("%f", *p);
}

int main()
{
	//printf_v1("Hello, World!\n");
	printf_v2("", 123);
	char dict[1] = {};
	char dict1[] = "";
	printf("%s %s", dict, dict1);
	printf_v3("Pre-format string %s Post-format string.\n", "Hi there.");
	printf_v4("%d", -23);
	puts("");
	printf_v5("%c", 'z');
	puts("");
	printf_v6("%f", 3.1415926);
	puts("");
	return 0;
}