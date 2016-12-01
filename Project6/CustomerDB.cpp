#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(String name) { // done, please do not edit
	this->bottles = 0;
	this->rattles = 0;
	this->diapers = 0;
	this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

int CustomerDB::size(void) {
	return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
	delete[] this->data;
}

void CustomerDB::clear(void) { // done, please do not edit
	delete[] this->data;
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
	assert(k >= 0 && k < this->length);
	return this->data[k];
}

/*
 * [NAME] operator[]
 * [Brief] overloads the [] operator for the CustomerDB
 * [Returns] Customer&: a reference to the customer 
 * [IN] String name: the name of the customer to access
 *
 * [Summary] Accesses and returns the customer with the given name or creates an element in the database 
 *  for the customer and returns the new element. Also implements amortized doubling of the customer database
 */
Customer& CustomerDB::operator[](String name) { // not done, your effort goes here
	if (isMember(name)) {
		// Find and return the customer with the given name 
		for (int k = 0; k < this->length; k++) {
			if (this->data[k].name == name) {
				return this->data[k];
			}
		}
	} else {
		// Reached max capacity, then double size of data array
		if (this->length + 1 == this->capacity) {
			// New data array
			Customer* newData = new Customer[capacity * 2];
			// Copy the data over
			for (int k = 0; k < this->length; k++) {
				newData[k] = this->data[k];
			}
			// Add the Customer to the new data array
			newData[length] = Customer(name);
			delete[] this->data;
			this->data = newData;
			this->capacity *= 2;
		} else {
			cout << name.c_str() << endl;
			this->data[length] = Customer(name);
		}
		this->length++;
		return this->data[length - 1]; 
	}
}


/*
 * [NAME] isMember
 * [Brief] checks if a customer is in the database
 * [Returns] bool: whether or not the customer is in the database
 * [IN] String name: name of the customer to search for
 *
 * [Summary] Returns whether or not a customer exists in the database with a given name
 */
bool CustomerDB::isMember(String name) { // not done, your effort goes here
	for (int k = 0; k < this->length; k++) {
		if (this->data[k].name == name) {
			return true;
		}
	}
	return false;
}


