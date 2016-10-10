
#include "comp.h";

int main() {
    char* strings[] = {"Make", "it", "so", "#1"};
    const unsigned int nstr = sizeof(strings)/sizeof(strings[0]);

    unsigned int i;
    
    // sort array
    qsort(strings, nstr, sizeof(strings[0]), comp);
    // print array
    for (i = 0; i < nstr; i++) {
        puts(strings[i]);
    }

