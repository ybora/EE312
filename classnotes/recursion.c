
#include <stdlib.h>
#include <stdio.h>

void printReverse(char* string);

int main(void) {
    printReverse("Hello");
    printf("\n");
    int* array = (int *) malloc(5 * sizeof(int));
    for (int k = 0; k < 5; k++) {
        array[k] = k+1;
    }
    printf("%d\n", sum(array, 5));
}

void printReverse(char* string) {
    if (*string == 0) {
        return;
    }
    else {
        printReverse(string + 1);
        putchar(*string);
    }
}

int sum(int a[], int n) {
    if (n == 0) return 0;
    return a[0] + sum(a + 1, n - 1);
}
