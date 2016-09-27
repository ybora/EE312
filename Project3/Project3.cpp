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
void insertNodeAtFront(Node*);
char updateInventory(String, String, int);
void updateNode(Node*, String, int);
void printError(String, String);
Node* createNewNode(String);
Node* isInLinkedList(Node*, String, String, int);
Node** findMaxNodes();

String bottle;
String diaper;
String rattle;
Node** nodes;

typedef struct Database {
	Node* root;
	int size;
	int numRattles;
	int numDiapers;
	int numBottles;
} Database;

/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */
Database db = {NULL, 0, 0, 0, 0};

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	/* your code here */
	Node* current = db.root;
	while (current != NULL) {
		StringDestroy(&(current->customer.name));
		free(current);
		current = current->next;
	}
	free(nodes);
	db.root = NULL;
	db.size = 0;
	db.numRattles = 0;
	db.numBottles = 0;
	db.numDiapers = 0;
	StringDestroy(&bottle);
	StringDestroy(&diaper);
	StringDestroy(&rattle);
}

void processSummarize() {
	Node** maxNodes = findMaxNodes();
	printf("There are %d Bottles, %d Diapers, and %d Rattles in inventory\n", db.numBottles, db.numDiapers, db.numRattles);
	printf("we have had a total of %d different customers\n", db.size);

	for (int k = 0; k < 3; k++) {
		if (k == 0) {
			if (maxNodes[k]->customer.bottles != 0)
				printf("%s has purchased the most Bottles (%d)\n", maxNodes[k]->customer.name.ptr, maxNodes[k]->customer.bottles);
			else 
				printf("no one has purchased any Bottles");
		}
		if (k == 1) {
			if (maxNodes[k]->customer.diapers != 0)
				printf("%s has purchased the most Diapers (%d)\n", maxNodes[k]->customer.name.ptr, maxNodes[k]->customer.diapers);
			else
				printf("no one has purchased any Diapers");
		}
		if (k == 2) {
			if (maxNodes[k]->customer.rattles != 0)
				printf("%s has purchased the most Rattles (%d)\n", maxNodes[k]->customer.name.ptr, maxNodes[k]->customer.rattles);
			else
				printf("no one has purchased any Rattles");
		}
	}
}

Node** findMaxNodes() {
	nodes = (Node**) malloc(3 * sizeof(Node*));

	Node* current = db.root;
	nodes[0] = current;
	nodes[1] = current;
	nodes[2] = current;

	while (current != NULL) {
		if (current->customer.bottles > nodes[0]->customer.bottles)
			nodes[0] = current;
		if (current->customer.diapers > nodes[1]->customer.diapers)
			nodes[1] = current;
		if (current->customer.rattles > nodes[2]->customer.rattles)
			nodes[2] = current;
		current = current->next;
	}
	return nodes;
}

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
		if (updateInventory(name, itemType, amount)) {
			Node* n = createNewNode(StringDup(&name));
			updateNode(n, itemType, amount);
			insertNodeAtFront(n);
		} else {
			printError(name, itemType);
		}
	} 

	StringDestroy(&name);
	StringDestroy(&itemType);
}

void insertNodeAtFront(Node* node) {
	node->next = db.root;
	db.root = node;
	db.size++;
}

void printError(String name, String itemType) {
	if (StringIsEqualTo(&itemType, &bottle)) {
		printf("Sorry %s, we only have %d %s\n", name.ptr, db.numBottles, itemType.ptr);
	}
	else if (StringIsEqualTo(&itemType, &diaper)) {
		printf("Sorry %s, we only have %d %s\n", name.ptr, db.numDiapers, itemType.ptr);
	}
	else if (StringIsEqualTo(&itemType, &rattle)) {
		printf("Sorry %s, we only have %d %s\n", name.ptr, db.numRattles, itemType.ptr);
	}
}

Node* createNewNode(String name) {
	Node* newNode = (Node *) malloc(sizeof(Node));

	newNode->next = NULL;
	newNode->customer.name = name;
	newNode->customer.bottles = 0;
	newNode->customer.diapers = 0;
	newNode->customer.rattles = 0;

	return newNode;
}

Node* isInLinkedList(Node* node, String name, String itemType, int amount) {
	Node* current = node;

	while (current != NULL) {
		if (StringIsEqualTo(&(current->customer.name), &name)) {
			if (updateInventory(name, itemType, amount)) {
				updateNode(current, itemType, amount);
				return current;
			}
		}
		current = current->next; 
	}
	return NULL;
}

char updateInventory(String name, String itemType, int amount) {
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
	} else {
		return 0;
	}	

}

void updateNode(Node* node, String itemType, int amount) {
	if (StringIsEqualTo(&itemType, &bottle)) {
		node->customer.bottles += amount;
	}
	else if (StringIsEqualTo(&itemType, &diaper)) {
		node->customer.diapers += amount;
	}
	else if (StringIsEqualTo(&itemType, &rattle)) {
		node->customer.rattles += amount;
	}
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
