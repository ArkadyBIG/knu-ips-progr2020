/*
 * lesson_k19_2020_01_28.cpp
 *
 *  Created on: Jan 28, 2020
 *      Author: KZ
 */
#include <string>
#include <iostream>

enum Gender { MALE, FEMALE, GMAIL };

struct Person {
	std::string name;
	int age;
	double height; // in cm
	Gender gender = Gender::GMAIL;

	Person(std::string name,int age, double height, Gender gender) {
		this->name = name;
		this->age = age;
		this->height = height;
		this->gender = gender;
	}

};

int main() {
	std::cout<<"hello world"<<std::endl;
	return 0;
}


