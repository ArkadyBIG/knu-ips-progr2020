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
	int id;
	static int max_id;
	std::string name;
	int age;
	double height; // in cm
	Gender gender = Gender::GMAIL;

	Person(std::string name,int age, double height, Gender gender) {
		this->name = name;
		this->age = age;
		this->height = height;
		this->gender = gender;
		this->id = max_id;
		max_id++;

	}
};
int Person::max_id = 0;

void write_text_file(Person person, std::string file_path) {
	std::ofstream file(file_path);
	file << person.id << std::endl;
	file << person.name << std::endl;
	file << person.age << std::endl;
	file << person.height << std::endl;
	file << person.gender << std::endl;
	file.close();
}

void edit_text_file(std::string path, Person person) {

}

int main() {
	std::cout<<"hello world"<<std::endl;
	write_text_file(Person("First Person",5,50,Gender::GMAIL),"text.txt");
	write_text_file(Person("Second Person",50,5,Gender::GMAIL),"text.txt");
	return 0;
}


