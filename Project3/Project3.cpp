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
void updateNode(Node*, String, String, int);
void printError(String, String);
Node* createNewNode();
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

void processSummarize() {

}

Node* findMaxNodes(String itemType) {
	Node** nodes = (Node**) malloc(3 * sizeof(Node*));

	Node* current = db.root;
	nodes[0] = current;
	nodes[1] = current;
	nodes[2] = current;

	while (current != NULL) {
		if (StringIsEqualTo(&itemType, &bottle)) {
			if (current->customer.bottles > nodes[0]->customer.bottles)
				nodes[0] = current;
		}
		else if (StringIsEqualTo(&itemType, &diaper)) {
			if (current->customer.diapers > nodes[1]->customer.diapers)
				nodes[1] = current;
		}
		else if (StringIsEqualTo(&itemType, &rattle)) {
			if (current->customer.rattles > nodes[2]->customer.rattles)
				nodes[2] = current;
		}
	}
	return max;
}

void processPurchase() {
	createItems();

 	String name;
	readString(&name);
	String itemType;
	readString(&itemType);
	int amount;
	readNum(&amount);

	printf("Purchase ");
	printf("%s ", name.ptr);
	printf("%s ", itemType.ptr);
	printf("%d\n", amount);

	Node* exists = isInLinkedList(db.root, name, itemType, amount);
	if (!exists) {
		if (updateInventory(name, itemType, amount)) {
			Node* n = createNewNode();
			updateNode(n, name, itemType, amount);
			insertNodeAtFront(n);
		}
	} 

	printf("bottles in inventory: %d\n", db.numBottles);
	printf("diapers in inventory: %d\n", db.numDiapers);
	printf("rattles in inventory: %d\n", db.numRattles);
	printLL();
	printf("------------------------------\n");

}

void insertNodeAtFront(Node* node) {
	node->next = db.root;
	db.root = node;
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

// TODO: add name param
Node* createNewNode() {
	Node* newNode = (Node *) malloc(sizeof(Node));

	newNode->next = NULL;
	newNode->customer.name = StringCreate("");
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
				updateNode(current, name, itemType, amount);
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
		printError(name, itemType);
		return 0;
	}	

}

void updateNode(Node* node, String name, String itemType, int amount) {
	node->customer.name = name;
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
