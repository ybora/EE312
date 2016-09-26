#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Merge.h"

void printArray(int* arr, size_t size) {
	char* comma = "";
	putchar('[');
	for (int i = 0; i < size; i++) {
		printf("%s%d", comma, arr[i]);
		comma = ", ";
	}
	putchar(']');
	puts("");
}

int main(void) {
	int* a = (int*)malloc(sizeof(int) * 5);
	a[0] = 1;
	a[1] = 3;
	a[2] = 5;
	a[3] = 7;
	a[4] = 9;
	int b[3] = { 2, 3, 4 };
	int new_size = 0;
	clock_t t1 = clock();
	int* merged = merge_no_dups(a, 5, b, 3, &new_size);
	clock_t t2 = clock();
	double dur = 1000.0*(t2 - t1) / CLOCKS_PER_SEC;
	printf("%d ms\n", dur);
	printArray(merged, new_size);
	free(a);
	a = NULL;
	return 0;
}
