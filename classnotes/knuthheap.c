

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int32_t* p = malloc(1);
    int32_t* q = malloc(1);
    free(p);
    int32_t * r = malloc(1);
    *p = 100;
    *q = 200;
    *r = 300;
    free(q);
}
