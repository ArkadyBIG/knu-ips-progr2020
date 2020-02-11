/*
 * lesson_k18-2020_02_11_sorting.cpp
 *
 *  Created on: Feb 11, 2020
 *      Author: KZ
 */
#include <iostream>
#include <cstddef>

namespace lesson_k18_2020_02_11_sorting {


void shell_sort(int* array, std::size_t size) {
	static const int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1 };

	for(auto gap: gaps) {
		int temp;
		for (std::size_t i = gap; i < size; i++) {
			temp = array[i];
			std::size_t j;
			for (j = i; j >= gap && array[j-gap]>temp; j-=gap ) {
				array[j] = array[j-gap];
			}
			array[j] = temp;
		}
	}
}


int main() {

	int test_array[] = {2,74,1,-43, 23, 123, 55, -4, 0, 1};
	std::size_t size = sizeof(test_array)/sizeof(test_array[0]);
	shell_sort(test_array, size);
	for(auto i: test_array) {
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;


	return 0;
}


}
