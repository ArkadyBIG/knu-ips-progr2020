/*
 * lesson_k19_2020_01_28.cpp
 *
 *  Created on: Jan 28, 2020
 *      Author: KZ
 */
#include <string>
#include <iostream>
#include <fstream>

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

void write_text_file(Person person, std::string file_path) {
	std::ofstream file(file_path);
	file << person.name << std::endl;
	file << person.age << std::endl;
	file << person.height << std::endl;
	file << person.gender << std::endl;
	file.close();
}

int main() {
	std::cout<<"hello world"<<std::endl;
	write_text_file(Person("First Person",5,50,Gender::GMAIL),"text.txt");
	return 0;
}


