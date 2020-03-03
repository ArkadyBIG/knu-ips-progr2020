/*
 * lesson_k19_2020_03_03_sparse_list.cpp
 *
 *  Created on: Mar 3, 2020
 *      Author: KZ
 */

#include <iostream>

namespace lesson_k19_2020_03_03_sparse_list {


struct SparseListNode {
	int value;
	std::size_t index;

	SparseListNode* next;
	SparseListNode (int value, std::size_t index, SparseListNode* next=nullptr):
		value(value), index(index), next(next) {}
};

struct SparseList {
	std::size_t size;
	std::size_t nonempty_size;
	SparseListNode* head;

	SparseList(std::size_t size): size(size), nonempty_size(0), head(nullptr) {}
	void print_with_index() {
		for(SparseListNode* current = head; current; current = current->next) {
			std::cout<<current->index<<": "<<current->value<<std::endl;
		}
	}

	void insert(int value, std::size_t index) {
		if (value == 0) {
			return;
		}
		if (index>size) {
			throw std::invalid_argument("Index greater than size");
		}
		SparseListNode* current = head;
		if (current == nullptr) {
			head = new SparseListNode(value, index);
			//size++;
			nonempty_size++;
			return;
		}
		//std::size_t current_position = 0;
		while (current) {
			if( ! current->next ) {
				break;
			}
			if (index > current->next->index) {
				break;
			}
//			if (current_position>index) {
//				break;
//			}

			current = current->next;

//			current_position++;
		}

		SparseListNode* new_node = new SparseListNode(value, index, current->next);
		if (current == nullptr) {

		}
		current->next = new_node;

	}
};


int main() {
	SparseList list(100);

	list.insert(10, 3);
	list.insert(-12, 10);
	list.insert(333, 5);
	list.insert(678, 21);
	list.print_with_index();
	return 0;
}

}

