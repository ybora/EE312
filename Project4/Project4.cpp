/*
 * Project4.c 
 *
 * Nav Saini
 * My Section Time
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"


bool binarySearch(const Set* self, int low, int high, int x);
/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way. 
 * Please NOTE, you are responsible for ensuring that the functions work correctly in 
 * your project solution. Just because the function works correctly in my solution does 
 * NOT mean that the function will work correctly in yours. 
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that 
 * the amount of storage available in the elements[] array is equal to length
 */


/* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*) malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*) malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;	
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }
	
	destroySet(self);
	createCopySet(self, other);
}

/* return true if x is an element of self */

/*
 * [NAME] isMemberSet
 * [Brief] checks if a number is in the set
 * [Returns] bool: whether or not the set contains a certain number
 * [IN] Set* self: pointer to the set being checked
 * [IN] int x: the value being searched for
 *
 * [Summary] Uses a helper binary search function to check if a certain number, x, is in the 
 *  given set
 */
bool isMemberSet(const Set* self, int x) {
	return binarySearch(self, 0, (self->len) - 1, x);
}

/*
 * [NAME] binarySearch
 * [Brief] performs a binary search 
 * [Returns] bool: whether or not the set contains a certain number
 * [IN] Set* self: pointer to the set being checked
 * [IN] int low: the index of the lowest element being checked
 * [IN] int high: the index of the highest element being checked
 * [IN] int x: the value being searched for
 *
 * [Summary] Performs a binary search to check for the existence of a number, x, in the sorted set
 */
bool binarySearch(const Set* self, int low, int high, int x) {
	if (low > high) return false;
	int mid = (low + high)/2;

	if (self->elements[mid] == x) return true;
	else if (self->elements[mid] > x) return binarySearch(self, low, mid - 1, x);
	else return binarySearch(self, mid + 1, high, x);
}

/*
 * add x as a new member to this set. 
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */

/*
 * [NAME] insertSet
 * [Brief] inserts a number into the set
 * [Returns] void
 * [IN] Set* self: pointer to the set 
 * [IN] int x: the value being added to the set
 *
 * [Summary] Adds a value to the given sorted set in the correct position to keep it sorted
 */
void insertSet(Set* self, int x) {
	int index = 0;
	int oldIndex = 0;

	if (isMemberSet(self, x)) return;

	/* Find the index at which to insert the value */
	while (index < self->len && x > self->elements[index]) {
		index++;
	}

	int* newSet = (int *) malloc((self->len + 1) * sizeof(int));

	/* Copy the initial set to the newly made one with the new element inserted */
	for (int k = 0; k < (self->len + 1); k++) {
		if (k == index) {
			newSet[k] = x;
		} else {
			newSet[k] = self->elements[oldIndex];
			oldIndex++;
		}
	}

	/* Free the initial set and reassign elements to the newly made array */
	destroySet(self);
	self->elements = newSet;
	self->len++;
}

/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.  
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the 
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array 
 * is almost definitely NOT worth the trouble
 */

/*
 * [NAME] removeSet
 * [Brief] removes a number from the set
 * [Returns] void
 * [IN] Set* self: pointer to the set 
 * [IN] int x: the value being removed
 *
 * [Summary] Removes a certain number, x, from the set and moves all the elements of the set back to keep it
 *  sorted and consistent with its length attribute
 */
void removeSet(Set* self, int x) {
	if (!isMemberSet(self, x)) return;

	int index = 0;

	/* Find the index of the element to remove */
	while (self->elements[index] < x) {
		index++;
	}

	// if (index == self->len) return;

	/* Move all the elements back one */
	for (int k = index; k < (self->len - 1); k++) {
		self->elements[k] = self->elements[k + 1];
	}

	self->len -= 1;
}

/* done for you already */
void displaySet(const Set* self) {
	int k;
	
	printf("{");

	if (self->len == 0) { 
		printf("}"); 
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			} else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}

/* return true if self and other have exactly the same elements */

/*
 * [NAME] isEqualToSet
 * [Brief] checks if two sets contain the same elements
 * [Returns] bool: whether or not the sets are the same
 * [IN] Set* self: pointer to the first set
 * [IN] Set* other: pointer to the second set
 *
 * [Summary] Iterates through each element of the sets to check if they are the same
 */
bool isEqualToSet(const Set* self, const Set* other) {
	if (self->len != other->len) return false;

	for (int k = 0; k < self->len; k++) {
		if (self->elements[k] != other->elements[k]) return false;
	}
	return true;
}

/* return true if every element of self is also an element of other */

/*
 * [NAME] isSubsetOf
 * [Brief] checks a set is a subset of another
 * [Returns] bool: whether or not the first set is a subset of the second
 * [IN] Set* self: pointer to the first set
 * [IN] Set* other: pointer to the second set
 *
 * [Summary] checks if each element of the first set, self, is also in the other set, other, by
 *  by iterating through each set and incrementing two separate indeces as appropriate
 */
bool isSubsetOf(const Set* self, const Set* other) {
	int index = 0;
	if (self->len == 0) return true;
	if (self->len > other->len) return false;

	for (int k = 0; k < other->len; k++) {
		/* if found a match, increment the index for the first set */
		if (self->elements[index] == other->elements[k])
			index++;
		/* once at the end of the first set, return true */
		if (index == self->len) 
			return true;
	}
	return false;
}

/* done for you */
bool isEmptySet(const Set* self) {
	return self->len == 0;
}

/* remove all elements from self that are not also elements of other */

/*
 * [NAME] intersectFromSet
 * [Brief] finds the intersection of two given sets
 * [Returns] void
 * [IN] Set* self: pointer to the first set
 * [IN] Set* other: pointer to the second set
 *
 * [Summary] Iterates through each element of the sets and adds an element to a newly allocated array
 *  if two matching elements are found. Puts the resulting set back into the first set, self.
 */
void intersectFromSet(Set* self, const Set* other) {
	int* newSet = (int*) malloc (self->len * sizeof(int));

	int k = 0;
	int j = 0;
	int index = 0;

	while (k < self->len && j < other->len) {
		/* if found a match, put it in the new array */
		if (self->elements[k] == other->elements[j]) {
			newSet[index] = self->elements[k];
			index++;
			k++;
			j++;
		/* if too small, increment the index for the first set */
		} else if (self->elements[k] < other->elements[j]){
			k++;
		/* if too big, increment the index for the second set */
		} else {
			j++;
		}
	}

	/* Free the initial set and reassign elements to the newly made array */
	destroySet(self);
	self->elements = newSet;
	self->len = index;

}

/* remove all elements from self that are also elements of other */

/*
 * [NAME] subtractFromSet
 * [Brief] subtracts two sets
 * [Returns] void
 * [IN] Set* self: pointer to the first set
 * [IN] Set* other: pointer to the second set
 *
 * [Summary] Iterates through each element of the sets and adds an element to a newly allocated array
 *  if there is not a matching element in the second array for each of the elements in the first array.
 *  Puts the resulting array back into the first set, self.
 */
void subtractFromSet(Set* self, const Set* other) {
	int* newSet = (int*) malloc (self->len * sizeof(int));

	int k = 0;
	int j = 0;
	int index = 0;

	while (k < self->len && j < other->len) {
		/* Match found, meaning don't put this element into the new array */
		if (self->elements[k] == other->elements[j]) {
			k++;
			j++;
		/* if the element in self is smaller than the current one in other, that means it is not possible to be found */
		} else if (self->elements[k] < other->elements[j]){
			newSet[index] = self->elements[k];
			index++;
			k++;
		/* keep looking, you're not there yet */
		} else {
			j++;
		}
	}

	/* copy left over elements from into the new set */
	while (k < self->len) {
		newSet[index++] = self->elements[k++];
	}

	destroySet(self);
	self->elements = newSet;
	self->len = index;
}

/* add all elements of other to self (obviously, without creating duplicate elements) */

/*
 * [NAME] unionInSet
 * [Brief] finds the union of two given sets
 * [Returns] void
 * [IN] Set* self: pointer to the first set
 * [IN] Set* other: pointer to the second set
 *
 * [Summary] Combines all unique elements of the first set, self, and the second set, other.
 */
void unionInSet(Set* self, const Set* other) {
	int* newSet = (int*) malloc ((self->len + other->len) * sizeof(int));

	int k = 0;
	int j = 0;
	int index = 0;

	while (k < self->len && j < other->len) {
		/* insert the kth element in self before the jth element in other into the new array */
		if (self->elements[k] < other->elements[j]) {
			newSet[index++] = self->elements[k++];
		/* insert the jth element in other before the kth element in self into the new array */
		} else if (self->elements[k] > other->elements[j]) {
			newSet[index++] = other->elements[j++];
		/* repeated element, so only insert one but increment both indeces */
		} else {
			newSet[index++] = self->elements[k];
			k++;
			j++;
		}
	}

	/* copy the leftover elements from other into the new array */
	while (j < other->len) {
		newSet[index++] = other->elements[j++];
	}

	/* copy the leftover elements from self into the new array */
	while (k < self->len) {
		newSet[index++] = self->elements[k++];
	}

	destroySet(self);
	self->elements = newSet;
	self->len = index;
}
