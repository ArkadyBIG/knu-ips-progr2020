/*
 * lesson_k19_2020_02_11_linked_list.cpp
 *
 *  Created on: Feb 11, 2020
 *      Author: KZ
 */
#include <iostream>
#include <cstddef>

namespace lesson_k19_2020_02_11_linked_list {

struct ListNode {
	int  value;
	ListNode* next;
	ListNode* prev;
};

struct List {
	std::size_t size;
	ListNode* head;
	ListNode* tail;
};

List create_list() {
	List result;
	result.size = 0;
	result.head = result.tail = nullptr;
	return result;
}

void append_to_list(List& list, int value) {
	ListNode* node = new ListNode;
	node->value = value;
	node->prev = list.tail;
	node->next = nullptr;
	if (list.tail) {
		list.tail->next = node;
		list.tail = node;
	} else {
		list.tail = list.head = node;
	}
	list.size++;

}

void print_list(const List& list) {

	for(ListNode* current_node = list.head;
			current_node;
			current_node = current_node->next) {
		std::cout<< current_node->value<<" ";
	}
	std::cout<<std::endl;
}




int main() {
	List list = create_list();
	append_to_list(list, 123);
	append_to_list(list,456);
	append_to_list(list,789);
	append_to_list(list,120);
	print_list(list);
	return 0;
}

}
