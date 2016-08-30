/*
 * Project1.cpp
 * 
 * Name: Navendu Saini
 * EE312 Spring 2016
 * SpellCheck
 */

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent 
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

void printString(char x[], int start, int end);
char isSmallLetter(char letter);
char isBigLetter(char letter);

void spellCheck(char article[], char dictionary[]) {
    int start = 0;
    int end = 0;

    while (article[start]) {
        while (!isSmallLetter(article[start]) && !isBigLetter(article[start])) {
            start++;
            if (!article[start]) return;
        }
        end = start;
        while ((isSmallLetter(article[end]) || isBigLetter(article[end]))) {
            end++;
        }
        printString(article, start, end);
        start = end;
    }
}

char checkString(char word[], char dictionary[]) {
    int index = 0;
    int dict = 0;

    // Keep checking word with current word in dictionary
    while  (word[index] == dictionary[dict]) {
        index++; dict++;
    }
    // If you get a match, word[index] will be \0 and dictionary[dict] will be \n
    if (dictionary[dict] == '\n') return 1;
    // Look for next word
    while (dictionary[dict] != '\n') {
        dict++;
    }
    return 1;
}

char isSmallLetter(char letter) {
    if (letter > 0x60 && letter < 0x7b) return 1;
    return 0;
}

char isBigLetter(char letter) {
    if (letter > 0x40 && letter < 0x5b) return 1;
    return 0;
}

void printString(char x[], int start, int end) {
    for (int k = start; k < end; k++) {
        printf("%c", x[k]);
    }
    printf("\n");
}







