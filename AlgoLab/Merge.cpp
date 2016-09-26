// Merge.cpp : Defines the entry point for the console application.
//

/*
* Merge two array with no duplicates, so that other is copied into
* self.
*/

#include "Merge.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void printArray(int* arr, size_t size);
/* Merge self and other's elements without duplicates, and return the pointer to
 * the merged array.  Update merged_size. */
int* merge_no_dups(int* self, int sl, const int* other, int ol, int* merged_size ) {
	int* merged = (int*)malloc(sizeof(int)*(sl + ol));
	int i = 0; int j = 0;
	int ind = 0;
	// Merge the two arrays.
	while (i < sl && j < ol) {	//If self's element < other's
		if (self[i] < other[j]) {
			merged[ind] = self[i];
			ind++;
			i++;
		}
		else if (self[i] > other[j]) {
			merged[ind] = other[j]; // if other's element < self's
			ind++;
			j++;
		}
		else if (self[i] == other[j]) {
			merged[ind] = other[j]; // if other's element = self's
			ind++;
			i++;
			j++;
		}
	}

	if (i == sl) {
		while (j < ol) {
			merged[ind] = other[j];
			j++;
			ind++;
		}
	}
	if (j == ol) {
		while (i < sl) {
			merged[ind] = self[i];
			i++;
			ind++;
		}
	}
	*merged_size = ind;
	return merged;
}

