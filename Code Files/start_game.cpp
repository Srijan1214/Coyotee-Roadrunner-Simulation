#include "game.h"
#include <iostream>
#include <fstream>
#include <string>

///This file is the consumer of the game project.
///Model/View/Consumer Design pattern
void read_from_config_file(int &r, int &c,int &no_of_initial_roadrunners,int &no_of_initial_coyote){
	std::ifstream config_file;
	config_file.open("config.txt");
	if (config_file.is_open()) {
		int count = 0;
		std::string line;
		try{
		while (getline(config_file, line)) {
			if (count == 0) {
				r=std::stoi(line.substr(3));
			}
			else if(count==1){
				c=std::stoi(line.substr(3));
			}else if(count ==2){
				no_of_initial_roadrunners=std::stoi(line.substr(28));
			}else if(count ==3){
				no_of_initial_coyote=std::stoi(line.substr(23));
			}
			count++;
		}
		}catch(...){
			std::cerr<<"Cannot read config file. Please maintain the format as the original file."<<std::endl;
			exit(EXIT_FAILURE);
		}
	}
	else {
		std::cerr << "Needs a config.txt file!" << std::endl;
		exit(0);
	}
}

///Runs game
void run_game(){
	long number_of_runs=0;
	int r, c,no_of_initial_roadrunners,no_of_initial_coyote;;
	read_from_config_file(r, c,no_of_initial_roadrunners,no_of_initial_coyote);
	game gm(r,c,no_of_initial_roadrunners,no_of_initial_coyote);
	while((gm.running)){
		gm.tick();
		if(number_of_runs>=2000){
			std::cerr<<"Too many runs. Make smaller parameters in Input file."<<std::endl;
			exit(EXIT_FAILURE);
		}
		number_of_runs++;
	}
	std::ofstream output_file("simulation_log.txt",std::ios::app);

	output_file << "No. of starting roadrunners :" << no_of_initial_roadrunners << "\n";
	output_file << "No. of starting coyote :" << no_of_initial_coyote << "\n";
	output_file << "No. of moves :" << gm.test_counter << "\n";
	output_file << "No. of remaining agents :" << gm.no_of_agents << "\n"<<"\n";
}

int main(){
	run_game();
}
