#include <iostream>
#include "LinkedListSet.h"

int main(void){
	
	LinkedListSet<int> mList;
	mList.print_elements();

	mList.insert_element(5);
	mList.insert_element(1);
	mList.insert_element(3);
	mList.insert_element(3);
	mList.insert_element(7);
	mList.insert_element(7);

	mList.print_elements();

	mList.remove_element(5);
	mList.print_elements();

	LinkedListSet<int> list1;
	list1.insert_element(1);
	list1.insert_element(3);
	list1.insert_element(2);

	LinkedListSet<int> list2;
	list2.insert_element(2);
	list2.insert_element(4);
	list2.insert_element(3);

	std::cout << "list 1 ";
	list1.print_elements();

	std::cout << "list 2 ";
	list2.print_elements();

	LinkedListSet<int> list3 = intersect(list1, list2);
	list3.print_elements();

	return 0;
}