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

char isSmallLetter(char letter);
char isBigLetter(char letter);
char checkString(char article[], int start, int end, char dictionary[]);
char convertToSmall(char letter);
void printString(char article[], int start, int end);


/*
 * [NAME] spellCheck
 * [Brief] checks if a word is spelled correctly
 * [Returns] void
 * [IN] char[] article, char[] dictionary
 *
 * [Summary] Checks each word in the article against the words in the dictionary to see if 
 * there is a match and prints it if there is no match
 */

void spellCheck(char article[], char dictionary[]) {
    int start = 0;
    int end = 0;

    while (article[start]) {
        while (!isSmallLetter(article[start]) && !isBigLetter(article[start])) {
            start++;
            if (!article[start]) return;
        }
        end = start;
        while (isSmallLetter(article[end]) || isBigLetter(article[end])) {
            end++;
        }
        if ((end - start) > 1) {
            if (!checkString(article, start, end, dictionary)) printString(article, start, end);
        }
        start = end;
    }
}

/*
 * [NAME] checkString
 * [Brief] checks if a word is in the dictionary
 * [Returns] 1 for found word, 0 for not found word
 * [IN] char[] article, int start, int end, char[] dictionary
 *
 * [Summary] Checks if a specific word in the article is in the dictionary
 * and returns a 1 if the word can be found in the dictionary or returns 0 otherwise
 */

char checkString(char article[], int start, int end, char dictionary[]) {
    char word[end - start + 1];
    int j = 0;
    for (int k = start; k < end; k++, j++) {
        word[j] = article[k];
    }
    word[j] = '\0';

    int index = 0;
    int dict = 0;
    while (dictionary[dict]) {
        // Keep checking word with current word in dictionary
        while  (convertToSmall(word[index]) == convertToSmall(dictionary[dict])) {
            if (!word[index] && (!dictionary[dict] || dictionary[dict] == '\n')) {
                return 1;
            }
            dict++;
            index++;
        }        
        // If you get a match, word[index] will be \0 and dictionary[dict] will be \n or \0
        if ((dictionary[dict] == '\n' || !dictionary[dict]) && !word[index]) {
            return 1;
        }
        index = 0;
        // Look for next word
        while (dictionary[dict++] != '\n') {
            if (!dictionary[dict]) {
                return 0;
            }
        }
    }
    return 0;
}

/*
 * [NAME] isSmallLetter
 * [Brief] checks if a character is a lowercase character
 * [Returns] 1 for lowercase letter, 0 otherwise
 * [IN] char letter
 *
 * [Summary] Checks if a letter is a lowercase letter, returns 1 if it is
 * and returns 0 otherwise
 */

char isSmallLetter(char letter) {
    if (letter >= 'a' && letter <= 'z') return 1;
    return 0;
}

/*
 * [NAME] isBigLetter
 * [Brief] checks if a character is an uppercase character
 * [Returns] 1 for uppercase letter, 0 otherwise
 * [IN] char letter
 *
 * [Summary] Checks if a letter is an uppercase letter, returns 1 if it is
 * and returns 0 otherwise
 */

char isBigLetter(char letter) {
    if (letter >= 'A' && letter <= 'Z') return 1;
    return 0;
}

/*
 * [NAME] convertToSmall
 * [Brief] returns the lowercase version of a letter
 * [Returns] lowercase letter
 * [IN] char letter
 *
 * [Summary] Checks if the given letter is uppercase, converts it to lowercase,
 * otherwise returns the original letter
 */

char convertToSmall(char letter) {
    if (isBigLetter(letter)) return letter + 0x20;
    return letter;
}

/*
 * [NAME] printString
 * [Brief] prints a word in the article
 * [Returns] void
 * [IN] char[] article, int start, int end
 *
 * [Summary] Given a starting and ending index, prints a part of the article,
 * used to print words in the article
 */

void printString(char article[], int start, int end) {
    for (int k = start; k < end; k++) {
        printf("%c", article[k]);
    }
    printf("\n");
}
