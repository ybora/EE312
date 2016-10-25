/* comp.c */
#include "comp.h"
#include <string.h>
#include <stdio.h>

int comp (const void* p1, const void* p2) {
    // p1 and p2 are pointers to strings, or pointers to pointers
    // to the starting char of char arrays.

    // Correct. a and b are pointers to the starting char of char arrays, and they are cast as such.
    char* a = *(char**) p1;
    char* b = *(char**) p2;
  
    // Wrong. a and b are treated as if they are pointers to the 
    // starting char of char arrays, but in reality, they are 
    // pointers to strings being wrongly cast as pointers to chars.

    // char* a = (char*) p1;
    // char* b = (char*) p2;
    return strcmp(a, b);
}
