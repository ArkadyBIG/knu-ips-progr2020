/*
 * lesson_k18_2020_01_28.cpp
 *
 *  Created on: Jan 28, 2020
 *      Author: KZ
 */
#include <string>
#include <iostream>
#include <fstream>

#include <cstdlib>
#include <ctime>


struct Snowman {
	std::string name;
	int num_eyes;
	bool has_bucket;
	double carrot_length; // in cm
	int num_balls;
	double* ball_radiuses; // from top to bottom, bucket and carrot on ball[0]
};

void save_to_txt(Snowman sman, std::string file_path) {
	std::ofstream file(file_path, std::ios::app);
	if ( ! file.is_open()) {
		std::cout<<"can't open file "<<file_path<<std::endl;
		return;
	}
	file << sman.name << " " << sman.num_eyes << " "
	     << sman.has_bucket << " " << sman.carrot_length << " "
		 << sman.num_balls << " ";
	for (int i=0; i<sman.num_balls; i++) {
		file << sman.ball_radiuses[i]<< " ";
	}
	file.close();
}


int main() {
	srand(time(nullptr));
	std::cout<<"trying to create snowman"<<std::endl;
	Snowman sman;
	sman.name = "Joe";
	sman.num_eyes = rand() % 3;
	sman.has_bucket = true;
	sman.carrot_length = (rand() % 20) + 1;
	sman.num_balls = (rand() % 3) + 1;
	sman.ball_radiuses = new double[sman.num_balls];
	double prev_radius = 0;
	for (int i=0; i < sman.num_balls; i++) {
		sman.ball_radiuses[i] = prev_radius + rand() % 21;
		prev_radius = sman.ball_radiuses[i];
	}
	std::cout<<"Snowman Joe created"<<std::endl;
	save_to_txt(sman,"database.txt");
	return 0;
}


