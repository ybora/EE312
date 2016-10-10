#include "comp.h"

int comp(const void* p1, const void* p2) {
    char* a = *((char **) p1);
    char* b = *((char**) p2);
    return strcmp(a, b);
}
