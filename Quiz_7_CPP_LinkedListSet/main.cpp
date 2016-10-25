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


	return 0;
}