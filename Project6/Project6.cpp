#include <stdio.h>
#include "String.h"
#include "Customer.h"
#include "CustomerDB.h"
#include <iostream>

void readString(String&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;

using namespace std;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	database.clear();
	num_bottles = 0;
	num_rattles = 0;
	num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the 
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(String word) {
	if (word == "Bottles") {
		return &num_bottles;
	} else if (word == "Diapers") {
		return &num_diapers;
	} else if (word == "Rattles") {
		return &num_rattles;
	}
	
	/* NOT REACHED */
	return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(String word, Customer& cust) {
	if (word == "Bottles") {
		return &cust.bottles;
	} else if (word == "Diapers") {
		return &cust.diapers;
	} else if (word == "Rattles") {
		return &cust.rattles;
	}
	
	/* NOT REACHED */
	return 0;
}


/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 * 
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the 
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(String type) {
	Customer* result = 0;
	int max = 0;
	for (int k = 0; k < database.size(); k += 1) {
		Customer& cust = database[k];
		int *p = selectInventItem(type, cust);
		if (*p > max) {
			max = *p;
			result = &cust;
		}
	}
	
	return result;
}

/*
 * [NAME] processPurchase
 * [Brief] processes a purchase 
 * [Returns] void
 * [IN] void
 *
 * [Summary] Processes a purchase by checking its validity and updating the inventory and customer db
 */
void processPurchase() {
	String name;
	readString(name);
	String itemType;
	readString(itemType);
	int amount;
	readNum(amount);

	if (amount > 0) {
		if (amount <= *selectInventItem(itemType)) {
			Customer cust = database[name];
			int* countitems = (selectInventItem(itemType, cust));
			*countitems += amount;
			database[name] = cust;

			*(selectInventItem(itemType)) -= amount;
		} else {
			cout << "Sorry " << name.c_str() << ", we only have " << *(selectInventItem(itemType)) << " " << itemType.c_str() << endl;
		}
	}
}

/*
 * [NAME] processSummarize
 * [Brief] processes the word "Summarize" in the input file
 * [Returns] void
 * [IN] void
 *
 * [Summary] Prints the number of each item available in the inventory, prints the size of the database (the number of valid customers),
 *  and prints the name, buyer, and quantity of the each of the most purchased item
 */
void processSummarize() {
	cout << "There are " << num_bottles << " Bottles, " << num_diapers << " Diapers and " << num_rattles << " Rattles in inventory" << endl;
	cout << "we have had a total of " << database.length << " different customers" << endl;

	Customer* maxBottles = findMax(String("Bottles"));
	Customer* maxDiapers = findMax(String("Diapers"));
	Customer* maxRattles = findMax(String("Rattles"));

	if (maxBottles != 0 && maxBottles->bottles != 0) {
		cout << maxBottles->name.c_str() << " has purchased the most Bottles (" << maxBottles->bottles << ")" << endl;
	} else {
		cout << "no one has purchased any Bottles" << endl;
	}

	if (maxDiapers != 0 && maxDiapers->diapers != 0) {
		cout << maxDiapers->name.c_str() << " has purchased the most Diapers (" << maxDiapers->diapers << ")" << endl;
	} else {
		cout << "no one has purchased any Diapers" << endl;
	}

	if (maxRattles != 0 && maxRattles->rattles != 0) {
		cout << maxRattles->name.c_str() << " has purchased the most Rattles (" << maxRattles->rattles << ")" << endl;
	} else {
		cout << "no one has purchased any Rattles" << endl;
	}

}

/*
 * [NAME] processInventory
 * [Brief] process an inventory update
 * [Returns] void
 * [IN] void
 *
 * [Summary] Increase the amount of items in each part of the inventory (bottles, diapers, rattles)
 */
void processInventory() {
	String itemType;
	readString(itemType);
	int amount;
	readNum(amount);

	*(selectInventItem(itemType)) += amount;
}