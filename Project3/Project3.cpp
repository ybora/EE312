/* 
 * EE312 Simple CRM Project
 *
 * YOUR INFO HERE!
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "MyString.h"
#include "Invent.h"

typedef struct Node {
	struct Node* next;
	Customer customer;
} Node;

void printLL();
void createItems();
Node* createNewNode(String, String, int);
void insertNodeAtFront(Node*);
char updateInventory(String, int);
Node* isInLinkedList(Node*, String, String, int);

String bottle;
String diaper;
String rattle;

typedef struct Database {
	Node* root;
	int numRattles;
	int numDiapers;
	int numBottles;
} Database;

/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */
Database db = {NULL, 0, 0, 0};

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	/* your code here */
	db.root = NULL;
	db.numRattles = 0;
	db.numBottles = 0;
	db.numDiapers = 0;
	StringDestroy(&bottle);
	StringDestroy(&diaper);
	StringDestroy(&rattle);
}

void processSummarize() {}

void processPurchase() {
	createItems();

 	String name;
	readString(&name);
	String itemType;
	readString(&itemType);
	int amount;
	readNum(&amount);

	Node* exists = isInLinkedList(db.root, name, itemType, amount);
	if (!exists) {
		if (updateInventory(itemType, amount)) {
			Node* n = createNewNode(name, itemType, amount);
			insertNodeAtFront(n);
		}
		printf("exists is null\n");
	} else {

		printf("exists is not null: %s was found and updated\n", exists->customer.name.ptr);
	}

	printf("bottles in inventory: %d\n", db.numBottles);
	printf("diapers in inventory: %d\n", db.numDiapers);
	printf("rattles in inventory: %d\n", db.numRattles);
	printLL();

}

void insertNodeAtFront(Node* node) {
	node->next = db.root;
	db.root = node;
}

Node* createNewNode(String name, String itemType, int amount) {
	Node* newNode = (Node *) malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->customer.name = name;
	newNode->customer.bottles = 0;
	newNode->customer.diapers = 0;
	newNode->customer.rattles = 0;

	if (StringIsEqualTo(&itemType, &bottle))
		newNode->customer.bottles += amount;
	else if (StringIsEqualTo(&itemType, &diaper))
		newNode->customer.diapers += amount;
	else if (StringIsEqualTo(&itemType, &rattle))
		newNode->customer.rattles += amount;

	return newNode;
}

Node* isInLinkedList(Node* node, String name, String itemType, int amount) {
	Node* current = node;

	while (current != NULL) {
		if (StringIsEqualTo(&(current->customer.name), &name)) {
			if (StringIsEqualTo(&itemType, &bottle) && amount <= db.numBottles) {
				current->customer.bottles += amount;
				db.numBottles -= amount;
			}
			else if (StringIsEqualTo(&itemType, &diaper) && amount <= db.numDiapers) {
				current->customer.diapers += amount;
				db.numDiapers -= amount;
			}
			else if (StringIsEqualTo(&itemType, &rattle) && amount <= db.numRattles) {
				current->customer.rattles += amount;
				db.numRattles -= amount;
			}
			return current;
		}
		current = current->next; 
	}
	return NULL;
}

char updateInventory(String itemType, int amount) {
	if (StringIsEqualTo(&itemType, &bottle) && amount <= db.numBottles) {
		db.numBottles -= amount;
		return 1;
	}
	else if (StringIsEqualTo(&itemType, &diaper) && amount <= db.numDiapers) {
		db.numDiapers -= amount;
		return 1;
	}
	else if (StringIsEqualTo(&itemType, &rattle) && amount <= db.numRattles) {
		db.numRattles -= amount;
		return 1;
	}
	return 0;
}

void processInventory() {
	createItems();

	String itemType;
	readString(&itemType);
	int amount;
	readNum(&amount);

	if (StringIsEqualTo(&itemType, &bottle)) {
		db.numBottles += amount;
	} else if (StringIsEqualTo(&itemType, &diaper)) {
		db.numDiapers += amount;
	} else if (StringIsEqualTo(&itemType, &rattle)) {
		db.numRattles += amount;
	}
	StringDestroy(&itemType);
}

void createItems() {
	bottle = StringCreate("Bottles");
	diaper = StringCreate("Diapers");
	rattle = StringCreate("Rattles");
}

void printLL() {
	Node* copy = db.root;
	while (copy != NULL) {
		printf("%s ", copy->customer.name.ptr);
		printf("%d ", copy->customer.bottles);
		printf("%d ", copy->customer.diapers);
		printf("%d\n", copy->customer.rattles);
		copy = copy->next;
	}
}
