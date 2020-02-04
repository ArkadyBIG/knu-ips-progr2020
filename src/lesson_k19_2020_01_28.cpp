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
	file.write((char*)&(person.id), sizeof( person.id ));
	std::size_t size = person.name.size();
	file.write((char*)&size, sizeof( size ));
	const char* buffer = person.name.c_str();
	file.write(buffer, size);
	file.write((char*)&(person.age), sizeof( person.age ));
	file.write((char*)&(person.height), sizeof( person.height ));
	file.write((char*)&(person.gender), sizeof( person.gender ));


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
		Person person;
		file.read((char*)&(person.id),sizeof(person.id));
		std::cout<<person.id<<std::endl;
		if (file.eof()) { break; }
		std::size_t size;
		file.read((char*)&size,sizeof(size));
		std::cout<<"size = "<<size<<std::endl;
		char* buffer = new char[size+1];
		file.read(buffer, size);
		buffer[size]='\0';
		person.name = buffer;
		std::cout<<person.name<<std::endl;
		file.read((char*)&(person.age), sizeof( person.age ));
		file.read((char*)&(person.height), sizeof( person.height ));
		file.read((char*)&(person.gender), sizeof( person.gender ));
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
	std::cout<<"sizeof person"<< sizeof(Person)<<std::endl;
	std::cout<<"sizeof string"<< sizeof(std::string)<<std::endl;

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

	write_binary_file(Person("Third Person with a really long and really really long name to test how it works",10,10,Gender::MALE),"binary.bin");
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
	std::string name = "test name";
	for (int i=0; i < 10; i++) {
		write_binary_file(Person(name,10*i+5,100*i+30,Gender::GMAIL),"binary.bin");
		name += " some long string ";
	}

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


