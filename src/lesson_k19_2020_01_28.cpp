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
	std::ofstream file(file_path, std::ios_base::app);
	file << "id=" << person.id << std::endl;
	file << "name=" <<person.name << std::endl;
	file << "age=" <<person.age << std::endl;
	file << "height=" <<person.height << std::endl;
	file << "gender=" <<person.gender << std::endl;
	file.close();
}

void refresh_file(std::string file_path) {
	std::ofstream file(file_path);
	file.close();
}

void edit_text_file(std::string file_path, int id, Person person) {
	std::ifstream old_file(file_path);
	std::ofstream new_file(file_path+".new.txt");
	std::string line;
	bool ignore_lines = false;

	while(getline(old_file,line)) {
		if (line.substr(0, 2) == "id") {
			int line_id = std::stoi(line.substr(3));
			if (id == line_id) {
				std::cout<<"found "<<line<<std::endl;
				person.id = id;
				write_text_file(person, file_path+".new.txt");
				ignore_lines = true;
			} else {
				ignore_lines = false;
				new_file << line <<std::endl ;
			}
		} else if (! ignore_lines){
			new_file << line <<std::endl ;
		}
	}
	old_file.close();
	new_file.close();

}

int main() {
	std::cout<<"hello world"<<std::endl;
	refresh_file("text.txt");
	std::cout<<"file refreshed"<<std::endl;
	write_text_file(Person("First Person",5,50,Gender::GMAIL),"text.txt");
	write_text_file(Person("Second Person",50,5,Gender::GMAIL),"text.txt");
	edit_text_file("text.txt",0,Person("First Person",5,55,Gender::MALE));
	return 0;
}


