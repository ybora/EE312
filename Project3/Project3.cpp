/* 
 * EE312 Simple CRM Project
 *
 * Name: Nav Saini
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "MyString.h"
#include "Invent.h"

#define BOTTLE 0
#define DIAPER 1
#define RATTLE 2

/* Node struct to define the LinkedList */
typedef struct Node {
	struct Node* next;
	Customer customer;
} Node;


void createItems();
void destroyItems();
void printSorry(String, String, int);
void insertNodeAtFront(Node*);
void updateNode(Node*, String, int);
void printError(String, String);
char updateInventory(String, String, int);
Node* createNewNode(String);
Node* isInLinkedList(Node*, String, String, int);
Node** findMaxNodes();

typedef struct Database {
	Node* root;
	int size;
	int numRattles;
	int numDiapers;
	int numBottles;
} Database;

Database db = {NULL, 0, 0, 0, 0};
String bottle;
String diaper;
String rattle;
Node** nodes;

/*
 * [NAME] reset
 * [Brief] resets the inventory and frees the customer linked list
 * [Returns] void
 * [IN] void
 *
 * [Summary] Iterates through the customer linked list and frees all memory allocated
 *  Also sets the inventory variables (diapers, rattles, and bottles) to 0
 */
void reset(void) {
	Node* current = db.root;

	/* Iterate through the LinkedList and free all nodes */
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
}

/*
 * [NAME] processSummarize
 * [Brief] processes the word "Summarize" in the input file
 * [Returns] void
 * [IN] void
 *
 * [Summary] Prints the number of each item available in the inventory, prints the size of the LinkedList (the number of valid customers),
 *  and prints the name, buyer, and quantity of the each of the most purchased item
 */
void processSummarize(void) {
	Node** maxNodes = findMaxNodes();

	printf("There are %d Bottles, %d Diapers, and %d Rattles in inventory\n", db.numBottles, db.numDiapers, db.numRattles);
	printf("we have had a total of %d different customers\n", db.size);

	/* Iterate through the maxNodes array to get max values for bottles, diapers, and rattles */
	for (int k = 0; k < 3; k++) {
		if (k == BOTTLE) {
			if (maxNodes[k] != NULL && maxNodes[k]->customer.bottles != 0)
				printf("%s has purchased the most Bottles (%d)\n", maxNodes[k]->customer.name.ptr, maxNodes[k]->customer.bottles);
			else 
				printf("no one has purchased any Bottles\n");
		}
		if (k == DIAPER) {
			if (maxNodes[k] != NULL && maxNodes[k]->customer.diapers != 0)
				printf("%s has purchased the most Diapers (%d)\n", maxNodes[k]->customer.name.ptr, maxNodes[k]->customer.diapers);
			else
				printf("no one has purchased any Diapers\n");
		}
		if (k == RATTLE) {
			if (maxNodes[k] != NULL && maxNodes[k]->customer.rattles != 0)
				printf("%s has purchased the most Rattles (%d)\n", maxNodes[k]->customer.name.ptr, maxNodes[k]->customer.rattles);
			else
				printf("no one has purchased any Rattles\n");
		}
	}

}

/*
 * [NAME] findMaxNodes
 * [Brief] finds the nodes with the max of each item
 * [Returns] Node** an array of pointers to Nodes
 * [IN] void
 *
 * [Summary] Goes through the LinkedList of customers to see which customer bought the most of each item
 *  and returns all the information in an array
 */
Node** findMaxNodes(void) {
	nodes = (Node**) malloc(3 * sizeof(Node*));

	Node* current = db.root;
	nodes[BOTTLE] = current;
	nodes[DIAPER] = current;
	nodes[RATTLE] = current;

	while (current != NULL) {
		if (current->customer.bottles >= nodes[BOTTLE]->customer.bottles)
			nodes[BOTTLE] = current;
		if (current->customer.diapers >= nodes[DIAPER]->customer.diapers)
			nodes[DIAPER] = current;
		if (current->customer.rattles >= nodes[RATTLE]->customer.rattles)
			nodes[RATTLE] = current;
		current = current->next;
	}
	return nodes;
}

/*
 * [NAME] processPurchase
 * [Brief] processes a purchase 
 * [Returns] void
 * [IN] void
 *
 * [Summary] Processes a purchase by checking its validity and updating the inventory and customer db
 */
void processPurchase(void) {
	createItems();

 	String name;
	readString(&name);
	String itemType;
	readString(&itemType);
	int amount;
	readNum(&amount);

	assert(amount >= 0);

	if (amount != 0) {
		/* Check if customer is already in LinkedList; if so, update inventory and node */
		Node* exists = isInLinkedList(db.root, name, itemType, amount);
		if (!exists) {
			/* If customer does not exist, update the inventory and node after checking if there is enough stock of a certain item*/
			if (updateInventory(name, itemType, amount)) {
				Node* n = createNewNode(StringDup(&name));
				updateNode(n, itemType, amount);
				insertNodeAtFront(n);
			/* If there is not enough items in the inventory, print an error message */
			} else {
				printError(name, itemType);
			}
		} 
	} 

	StringDestroy(&name);
	StringDestroy(&itemType);

	destroyItems();
}


/*
 * [NAME] insertNodeAtFront
 * [Brief] adds a node to the front of the LinkedList
 * [Returns] void
 * [IN] Node* node: the node to add
 *
 * [Summary] Adds the node to the head of the LinkedList to allow for O(1) insertion 
 *  and updates the size of the LinkedList
 */
void insertNodeAtFront(Node* node) {
	node->next = db.root;
	db.root = node;
	db.size++;
}

/*
 * [NAME] printError
 * [Brief] prints an appropriate error message based on the item 
 * [Returns] void
 * [IN] String name: name of the customer
 * [IN] String itemType: type of item (bottles, diapers, rattles)
 *
 * [Summary] Prints a sorry message based on the name of the customer and the type of item
 */
void printError(String name, String itemType) {
	if (StringIsEqualTo(&itemType, &bottle)) {
		printSorry(name, itemType, db.numBottles);
	}
	else if (StringIsEqualTo(&itemType, &diaper)) {
		printSorry(name, itemType, db.numDiapers);
	}
	else if (StringIsEqualTo(&itemType, &rattle)) {
		printSorry(name, itemType, db.numRattles);
	}
}

/*
 * [NAME] printSorry
 * [Brief] prints a personalized sorry message for each customer/item
 * [Returns] void
 * [IN] String name: name of the customer
 * [IN] String itemType: type of item (bottles, diapers, rattles)
 * [IN] int amount: the amount of the item
 *
 * [Summary] Prints a sorry message based on the given parameters
 */
void printSorry(String name, String itemType, int amount) {
	printf("Sorry ");
	StringPrint(&name);
	printf(", we only have %d ", amount);
	StringPrint(&itemType);
	printf("\n");
}	

/*
 * [NAME] createNewNode
 * [Brief] creates a new customer node with the given name
 * [Returns] Node*: a pointer to the created Node
 * [IN] String name: name of the customer
 *
 * [Summary] Creates a node with a customer's name and all other purchase values set to 0.
 *  Use before inserting a Node into LinkedList with insertNodeAtFront
 */
Node* createNewNode(String name) {
	Node* newNode = (Node *) malloc(sizeof(Node));

	newNode->next = NULL;
	newNode->customer.name = name;
	newNode->customer.bottles = 0;
	newNode->customer.diapers = 0;
	newNode->customer.rattles = 0;

	return newNode;
}


/*
 * [NAME] isInLinkedList
 * [Brief] checks if a customer is already part of the LinkedList (has already made a valid purchase)
 * [Returns] Node*: a pointer to the Node mapping to the customer
 * [IN] Node* node: the LinkedList to look through
 * [IN] String name: name of the customer
 * [IN] String itemType: type of item (bottles, diapers, rattles)
 *
 * [Summary] Checks if a given node is in a given LinkedList (usually the customer LinkedList) and
 *  updates the inventory and node after making the appropriate check for quantity in the inventory
 */
Node* isInLinkedList(Node* node, String name, String itemType, int amount) {
	Node* current = node;

	while (current != NULL) {
		/* check if current customer name is the same as that passed in */
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

/*
 * [NAME] updateInventory
 * [Brief] updates the inventory 
 * [Returns] char: 1 or 0 describing whether or not there is enough room in the inventory for a purchase
 * [IN] String name: name of the customer
 * [IN] String itemType: type of item (bottles, diapers, rattles)
 * [IN] int amount: the amount of hte item
 * 
 * [Summary] Updates the inventory if there is enough room to make a purchase
 */
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

/*
 * [NAME] updateNode
 * [Brief] update the amount of an item purchased by the customer
 * [Returns] void
 * [IN] Node* node: the node to be updated
 * [IN] String itemType: type of item (bottles, diapers, rattles)
 * [IN] int amount: the amount of hte item
 *
 * [Summary] Updates the amount of an item purchased by a customer by the given amount
 */
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

/*
 * [NAME] processInventory
 * [Brief] process an inventory update
 * [Returns] void
 * [IN] void
 *
 * [Summary] Increase the amount of items in each part of the inventory (bottles, diapers, rattles)
 */
void processInventory(void) {
	createItems();

	String itemType;
	readString(&itemType);
	int amount;
	readNum(&amount);

	assert(amount >= 0);

	if (StringIsEqualTo(&itemType, &bottle)) {
		db.numBottles += amount;
	} else if (StringIsEqualTo(&itemType, &diaper)) {
		db.numDiapers += amount;
	} else if (StringIsEqualTo(&itemType, &rattle)) {
		db.numRattles += amount;
	}
	StringDestroy(&itemType);

	destroyItems();
}

/*
 * [NAME] createItems
 * [Brief] creates the string for each type of item (bottles, diapers, rattles)
 * [Returns] void
 * [IN] void
 *
 * [Summary] Creates a string for each type of item (bottles, diapers, rattles)
 */
void createItems(void) {
	bottle = StringCreate("Bottles");
	diaper = StringCreate("Diapers");
	rattle = StringCreate("Rattles");
}

/*
 * [NAME] destroyItems
 * [Brief] destroys global variable strings
 * [Returns] void
 * [IN] void
 *
 * [Summary] Destroy the string created for each type of item in the inventory
 */
void destroyItems() {
	StringDestroy(&bottle);
	StringDestroy(&diaper);
	StringDestroy(&rattle);
}

