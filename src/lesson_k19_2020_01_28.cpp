/*
 * lesson_k19_2020_01_28.cpp
 *
 *  Created on: Jan 28, 2020
 *      Author: KZ
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
//namespace k19_2020_01_28 {
enum Gender { MALE, FEMALE, GMAIL };

struct Person {
	int id;
	static int max_id;
	std::string name="Joe";
	int age;
	double height; // in cm
	Gender gender = Gender::GMAIL;

	Person() = default;
//	{
//		this->age = 111;
//		this->height = 222;
//		this->id = -1;
//	};

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

void write_binary_file(Person person, std::string file_path) {
	std::ofstream file(file_path, std::ios_base::app | std::ios_base::binary);
	std::size_t size = sizeof(person);
	std::cout<<"size = "<<size<<std::endl;
	file.write((char*)&size, sizeof( size ));

	file.write((char*)&person,sizeof(person));
//	file << "id=" << person.id << std::endl;
//	file << "name=" <<person.name << std::endl;
//	file << "age=" <<person.age << std::endl;
//	file << "height=" <<person.height << std::endl;
//	file << "gender=" <<person.gender << std::endl;
	file.close();
}

std::vector<Person> read_binary_file(std::string file_path) {
	std::vector<Person> result;
	std::ifstream file(file_path, std::ios_base::binary);
	while(!file.eof()) {
		std::size_t size;
		file.read((char*)&size,sizeof(size));
		if (file.eof()) { break; }
		std::cout<<"size = "<<size<<std::endl;
		Person person;
		file.read((char*)&person,size);
		result.push_back(person);
	}
	//result.pop_back();
	return result;

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
	refresh_file("binary.bin");
	write_binary_file(Person("First Person",5,50,Gender::MALE),"binary.bin");
	write_binary_file(Person("Second Person",50,5,Gender::FEMALE),"binary.bin");


	std::cout<<"written to binary"<<std::endl;
	std::vector<Person> persons = read_binary_file("binary.bin");
	std::cout<<persons.size()<<std::endl;
	for(const auto& person:persons) {
		std::cout << "id=" << person.id << std::endl;
		std::cout << "name=" <<person.name << std::endl;
		std::cout << "age=" <<person.age << std::endl;
		std::cout << "height=" <<person.height << std::endl;
		std::cout << "gender=" <<person.gender << std::endl;
	}

	write_binary_file(Person("Third Person",10,10,Gender::MALE),"binary.bin");
	std::cout<<"written to binary"<<std::endl;
	persons = read_binary_file("binary.bin");
	std::cout<<persons.size()<<std::endl;
	for(const auto& person:persons) {
		std::cout << "id=" << person.id << std::endl;
		std::cout << "name=" <<person.name << std::endl;
		std::cout << "age=" <<person.age << std::endl;
		std::cout << "height=" <<person.height << std::endl;
		std::cout << "gender=" <<person.gender << std::endl;
	}
	return 0;


	refresh_file("text.txt");
	std::cout<<"file refreshed"<<std::endl;
	write_text_file(Person("First Person",5,50,Gender::GMAIL),"text.txt");
	write_text_file(Person("Second Person",50,5,Gender::GMAIL),"text.txt");
	edit_text_file("text.txt",0,Person("First Person",5,55,Gender::MALE));
	return 0;
}

//}


