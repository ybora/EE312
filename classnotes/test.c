
#include <stdlib.h>
#include <stdio.h>

void doit(char[], char[]);

void doit(char x[], char y[]) {
    x = y;
    x[3] = ' ';
}

int main(void) {
    char x[4] = "Hey";
    char y[4] = "Joe";
    doit(x, y);
    printf("%s %s", x, y);
}

