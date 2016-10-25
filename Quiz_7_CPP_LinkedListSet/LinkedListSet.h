#ifndef __LINKEDLISTSET_HPP__
#define __LINKEDLISTSET_HPP__

#include <iostream>

// FYI Template classes must always be in header files :)
// You should google why this makes sense

/** 
 * @file LinkedListSet.h
 * Simple linked list implementation of a set. This class is templated,
 * and supports any type that supports the following operators <,>,=. 
 *
 * @brief Simple doubly linked list set class. The list elements are ordered
 * For faster processing.
 */

//Note typename is a c++11 syntax
// Change to class T if compiling with old compiler
template <typename T>
class LinkedListSet{
private:

	// Private helper types
	struct Node {
		Node* prev = this;
		Node* next = this;
		T data;

		//Constructors (provided)
		Node(const T& x): data{x} {}
		Node(void): data(0xdeadbeef) {}

		//Helper functions for convenience
		bool end(void)   { return next == this; }
		bool begin(void) { return prev == this; }

		//Used when destroying the Node
		void wrap(void)	 { prev = this; next = this; return; }
	};

    // Please Write this private helper function
    // Determines if the list is empty
	bool isEmpty(void);

	// Find the location of the element in the set
	// return true if element is in set and update n with this location
	// return false if element is not in set, and update n with the location greater than this element
	bool is_element(const T& x, Node*& n); //Note: the second argument is read as n is a reference to a Node pointer
										   // This allows me to update the Node pointer in the function

	// Private Variables
    // Feel free to add more, I recommend you add dummy head/tail nodes (sentinel nodes)
	Node* mList;
    //Pointers to Sentinel Nodes
	Node* head; //Next always points to the first element of the list, prev points to self
    Node* tail; //Prev always points to the last element in the list, next points to self
	
    int length;
    
    //Convenience functions
    Node* Head(void){ return head->next; }
    Node* Tail(void){ return tail->prev; }

public:
    
    //Write a default constructor and a destructor
	LinkedListSet(void);
	~LinkedListSet(void);

	//Class interface

	/**
	 * Is the Element in the set?
	 */
	bool is_element(const T& x);

	/**
	 * Insert the Element into the set
	 *  If exists, then quietly do nothing
	 */
	void insert_element(const T& x);

	/**
	 * Remove element from the set, if the element doesn't
	 *  exist, then quietly do nothing
	 */
	void remove_element(const T& x);

	/**
	 * Print the elements
	 */
	void print_elements(void);

    // Done for you
	int size(void) { return length; }

};
//====================BEGIN WRITING CODE========================================
// Please complete the following functions
// Note, you are allowed to add more helper functions to the class if you want.
// However, things that should only be used inside the class must be made private

template <typename T>
bool LinkedListSet<T>::isEmpty(void){
    return head->next == tail;
}

//================= Constructor ==============
template <typename T>
LinkedListSet<T>::LinkedListSet(void){

	head = new Node();
	tail = new Node();

	head->next = tail;
	tail->prev = head;

    return;
} //End Destructor
//================= Destructor ==============
template <typename T>
LinkedListSet<T>::~LinkedListSet(void) {
	Node* node = head->next;
	while(node != tail) {
		node->prev->wrap();
		delete node->prev;
		node = node->next;
		length--;
	}

	node->prev->wrap();
	delete node->prev;
	length--;

	node->wrap();
	delete node;

	return;

} //End Destructor


//================= is_element ==============
//Scan through the list using cursor n looking for element x
//First, set n to start of the list and scan forward
//if find x then return true
//note: if x < n->data then no element is found
//hint: n can be used to quickly determine the insert point in the set.
template <typename T>
bool LinkedListSet<T>::is_element(const T& x, Node*& n){
    if (n == nullptr) {
        n = head->next;
    }

    while(!n->end()) {
        if (n->data == x) {
            return true;
        } else if (x < n->data) {
        	return false;
        } else {
             n = n->next;
         }
    }

    return false; //Obviously not correct code
} // End is_element with search

//Provided for you
template <typename T>
bool LinkedListSet<T>::is_element(const T& x){
	if( isEmpty() ) return false;

	Node* node = nullptr;
	return is_element(x, node);
} // End is_element


//================= INSERT ==============
template <typename T>
void LinkedListSet<T>::insert_element(const T& x){

	Node* n = nullptr;

	if (!is_element(x, n)) {
		Node* newNode = new Node(x);
		n->prev->next = newNode;
		newNode->next = n;
		newNode->prev = n->prev;
		n->prev = newNode;
		this->length++;
	}
}

//================= Remove ELEMENT ==============
// Provided
template <typename T>
void LinkedListSet<T>::remove_element(const T& x){
	Node* node = nullptr;

	// is_element handles all the checks for us
	if( is_element(x, node) ){
		node->prev->next = node->next;
		node->next->prev = node->prev;
		node->wrap();
		length--;
		delete node;
	}
	return;
}

//================= PRINT ELEMENTS ==============

template <typename T>
void LinkedListSet<T>::print_elements(void){
	if( isEmpty() ) return;

	Node* node = head->next;
	std::cout << "{";
	while( !node->end() ){
		
		if( node->next->end() ){
			std::cout << node->data << "}";

		} else{ 
			std::cout << node->data << ", ";
		}
		node = node->next;
	}
	std::cout << std::endl;
	return;
}


#endif /*__LINKEDLISTSET_HPP__*/
