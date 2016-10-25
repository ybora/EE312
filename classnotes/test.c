
#include <stdlib.h>
#include <stdio.h>

void doit(char[], char[]);

void doit(char x[], char y[]) {
    x = y;
    x[3] = ' ';
}

int main(void) {
    int** arrays = (int **) malloc (5 * sizeof(int*));
    for (int k = 0; k < 5; k++) {
        arrays[k] = (int *) malloc (5 * sizeof(int));
    }

    for (int k = 0; k < 5; k++) {
        for (int j = 0; j < 5; j++) {
            arrays[k][j] = 1;
        }
    }

    for (int k = 0; k < 5; k++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", arrays[k][j]);
        }
        printf("\n");
    }
}

