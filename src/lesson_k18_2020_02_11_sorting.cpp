/*
 * lesson_k18-2020_02_11_sorting.cpp
 *
 *  Created on: Feb 11, 2020
 *      Author: KZ
 */
#include <iostream>
#include <algorithm>
#include <cstddef>
#include <ctime>

namespace lesson_k18_2020_02_11_sorting {


void insertion_sort_naive(int* array, std::size_t size) {
	for (std::size_t i = 1; i < size; i++) {
		for (std::size_t j = i; j>0 && array[j-1]>array[j];j--) {
			std::swap(array[j],array[j-1]);
		}
	}
}

void insertion_sort_smarter(int* array, std::size_t size) {
	for (std::size_t i = 1; i < size; i++) {
		int temp = array[i];
		std::size_t j;
		for (j = i; j>0 && array[j-1]>temp;j--) {
			array[j] = array[j-1];
		}
		array[j] = temp;
	}
}

void shell_sort(int* array, std::size_t size) {
	static const std::size_t gaps[] = {701, 301, 132, 57, 23, 10, 4, 1 };

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





void merge(int* source, int* destination, std::size_t begin, std::size_t middle, std::size_t end) {
	std::size_t first=begin, second = middle;
	for (std::size_t i = begin; i<end; i++) {
		if ((first<middle) && (second>=end || source[first]<=source[second])) {
			destination[i]=source[first];
			first++;
		} else {
			destination[i]=source[second];
			second++;
		}
	}
}


void merge_sort_twoarrays(int* source, int* destination, std::size_t begin, std::size_t end) {
	if (end-begin<2) {
		return;
	}
	std::size_t middle = (end + begin)/2;
	merge_sort_twoarrays(destination, source,begin,middle);
	merge_sort_twoarrays(destination, source,middle,end);
	merge(source, destination, begin, middle, end);
}

void merge_sort_topdown(int* array, std::size_t size) {
	int * destination = new int[size];
	std::copy(array, array+size, destination);
	merge_sort_twoarrays(destination, array, 0, size);
	delete [] destination;
}

void merge_sort_bottomup(int* array, std::size_t size) {
	int * destination = new int[size];

	for (std::size_t width = 1; width<size; width*=2) {
		for(std::size_t i = 0; i<size; i+=width*2) {
			std::size_t middle = std::min(i+width, size);
			std::size_t end = std::min(i+2*width, size);
			merge(array, destination, i, middle, end);
		}
		std::copy(destination, destination+size,array);
	}
	delete [] destination;
}

void test_memory_leaks() {
	int test_array[] = {2,74,1,-43, 23, 123, 55, -4, 0, 1, -12345};
	std::size_t size = sizeof(test_array)/sizeof(test_array[0]);
	while (true) {
		merge_sort_topdown(test_array, size);
	}
}

void compare_merge_sorts(std::size_t size) {
	int* array = new int[size];
	for(std::size_t i =0; i<size; i++) {
		array[i] = rand();
	}
	int* array_copy = new int[size];
	std::copy(array, array+size,array_copy);

	auto begin = std::clock();
	merge_sort_topdown(array,size);
	auto end = std::clock();
	std::cout<<"topdown: "<<1000.0 * (end-begin) / CLOCKS_PER_SEC<<" ms"<<std::endl;

	begin = std::clock();
	//merge_sort_bottomup(array_copy,size);
	insertion_sort_smarter(array_copy,size);
	end = std::clock();
	std::cout<<"insertion_sort_smarter: "<<1000.0 * (end-begin) / CLOCKS_PER_SEC<<" ms"<<std::endl;
	delete [] array;
	delete [] array_copy;
}


int main() {

	int test_array[] = {2,74,1,-43, 23, 123, 55, -4, 0, 1, -12345};
	std::size_t size = sizeof(test_array)/sizeof(test_array[0]);
	//shell_sort(test_array, size);
	//insertion_sort_smarter(test_array, size);


	merge_sort_bottomup(test_array, size);
	for(auto i: test_array) {
		std::cout<<i<<" ";
	}
	std::cout<<std::endl;

	compare_merge_sorts(1e5);

//	std::cout<<"test for memory leaks"<<std::endl;
//	test_memory_leaks();


	return 0;
}


}
