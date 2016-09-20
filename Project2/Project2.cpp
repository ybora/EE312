/*
 * Replace this comment with the standard EE312 file header!
 */

#include <assert.h>
#include <string.h>
/*#include "MemHeap.h"*/ /*Removed: Michael Bartling: 06/21/2016*/
#include <stdlib.h>
#include "String.h"
#include <stdio.h>

/* use these two macros and the function functions if you want -- not required */
#define SIGNATURE (~0xdeadbeef)

/** STRING(s)
 * Helper macro for accessing ut String object (if applicable)
 * [INPUT] pointer to cstring
 * [OUTPUT] pointer to UT String object (if applicable)
 */
#define STRING(s) ((String*)(s - 3*sizeof(uint32_t)))

/* this simple function can be useful when you implement stage 4
 * you are not required to use the function, and you can implement stage 4 without it */
int32_t isOurs(char* s) {
    /*if (!isHeapVar(s)) { return 0; }*//*Removed: Michael Bartling: 06/21/2016*/
    if (STRING(s)->check == SIGNATURE) { return 1; }
    else { return 0; }
}

/* allocate a utstring on the heap, initialize the string correctly by copying
 * the characters from 'src' and return a pointer to the first character of actual string data 
 *
 * [NAME] utstrdup
 * [Brief] Duplicates a c-style string as a UT String
 * [Returns] The pointer to the string in the UT String 
 * [IN] char* src: The string to duplicate
 *
 * [Summary] Takes in a c-style string and converts it to a UT String
 *  by finding its length, capacity, and assigning it the signature
 */
char* utstrdup(const char* src) 
{
	int length = 0;
	int k;
	for (k = 0; src[k]; k++) {
		length++;
	}

	// Allocate enough memory for the String struct, the length of the string and a null character
	String* utstr = (String *) malloc(sizeof(String) + length + 1);
	utstr->length = length;
	utstr->capacity = length;
	utstr->check = SIGNATURE;

	// Copy the data from the string into the UT String
	for (k = 0; k < length; k++) {
		utstr->data[k] = src[k];
	}
	utstr->data[k] = 0;

	return utstr->data;
}



/* the parameter 'utstr' must be a utstring. Find the length of this string by accessing the meta-data
 * and return that length 
 *
 * [NAME] utstrlen
 * [Brief] Finds the length of the UT String
 * [Returns] The length of the UT String
 * [IN] char* utstr: the string to get the length of
 *
 * [Summary] Checks the specified memory location in the String struct for
 *  its length
 */
uint32_t utstrlen(const char* utstr) 
{
	assert(STRING(utstr)->check == SIGNATURE);
	return STRING(utstr)->length;
}

/* s must be a utstring. suffix can be an ordinary string (or a utstring)
 * append the characters from suffix to the string s. Do not allocate any additional storage, and
 * only append as many characters as will actually fit in s. Update the length meta-data for utstring s
 * and then return s 
 *
 * [NAME] utstrcat
 * [Brief] Adds the suffix to the end of the given string
 * [Returns] The concatenated string
 * [IN] char* s: the string to add to
 * [IN] char* suffix: the string to add to the end
 *
 * [Summary] Concatenates the suffix to the source string 
 */
char* utstrcat(char* s, const char* suffix) 
{
	assert(isOurs(s));
	int length = utstrlen(s);
	int k;

	// Iterate till the end of the suffix string or the capacity of the UT String
	for (k = length; suffix[k - length] && k < STRING(s)->capacity; k++) {
		s[k] = suffix[k - length];
	}
	s[k] = 0;
	STRING(s)->length = k;

	return s;
}

/* 'dst' must be a utstring. 'src' can be an ordinary string (or a utstring)
 * overwrite the characters in dst with the characters from src. Do not overflow the capacity of dst
 * For example, if src has five characters and dst has capacity for 10, then copy all five characters
 * However, if src has ten characters and dst only has capacity for 8, then copy only the first 8
 * characters. Do not allocate any additional storage, do not change capacity. Update the length
 * meta-data for dst and then return dst 
 * 
 * [NAME] utstrcpy
 * [Brief] Copies the src string into the destination
 * [Returns] The copied string
 * [IN] char* dst: the destination to copy to
 * [IN] char* src: the string to copy to the destination
 *
 * [Summary] Copies the source string into the destination string
 */
char* utstrcpy(char* dst, const char* src) 
{
	assert(isOurs(dst));
	int k;

	// Iterate till the end of the source or the capacity of the destination
	for (k = 0; k < strlen(src) && k < STRING(dst)->capacity; k++) {
		dst[k] = src[k];
	}
	dst[k] = 0;
	STRING(dst)->length = k;

	return dst;
}

/* self must be a utstring. deallocate the storage for this string
 * (i.e., locate the start of the chunk and call free to dispose of the chunk, note that the start of
 * the chunk will be 12 bytes before *self) 
 *
 * [NAME] utstrfree
 * [Brief] Frees the UT String
 * [Returns] void
 * [IN] char* self: the UT String to free
 *
 * [Summary] Frees the memory allocated for the UT String that is passed in
 */
 void utstrfree(char* self) {
	assert(isOurs(self));
	free(STRING(self));
}

/* s must be a utstring.
 * ensure that s has capacity at least as large as 'new_capacity'
 * if s already has capacity equal to or larger than new_capacity, then return s
 * if s has less capacity than new_capacity, then allocate new storage with sufficient space to store
 * new_capacity characters (plus a terminating zero), copy the current characters from s into this
 * new storage. Update the meta-data to correctly describe new new utstring you've created, deallocate s
 * and then return a pointer to the first character in the newly allocated storage 
 *
 * [NAME] utstrrealloc
 * [Brief] Increases the capacity of the given UT String
 * [Returns] The newly created UT String
 * [IN] char* s: the string to reallocate
 * [IN] uint32_t new_capacity: the new capacity for the UT String
 *
 * [Summary] Increases the capacity of the given UT String to the specified new capacity
 *  by allocating more memory and then freeing the originally occupied memory
 */
char* utstrrealloc(char* s, uint32_t new_capacity) {
	assert(isOurs(s));

	// Only reallocate if the new capacity is greater than the original
	if (new_capacity > STRING(s)->capacity) {
		String* new_string = (String *) malloc(sizeof(String) + new_capacity + 1);
		strcpy(new_string->data, s);
		new_string->length = utstrlen(s);
		new_string->capacity = new_capacity;
		new_string->check = STRING(s)->check;
		utstrfree(s);
		return new_string->data;
	}
	return s;
}
