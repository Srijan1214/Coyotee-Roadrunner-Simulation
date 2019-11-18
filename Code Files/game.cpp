#include "game.h"
#include <iostream>
#include <time.h>
#include "board.h"

///constructor initializes everything
///starts the game
game::game(int rows,int columns,int number_of_roadrunner,int number_of_coyote):
no_of_rows(rows),no_of_columns(columns),board_obj(board::Instance(rows,columns)),
test_counter(0),running(true){
	srand(time(NULL));
	generate_random_coyotes(number_of_roadrunner);
	generate_random_roadrunners(number_of_coyote);
}


///only runs if the bool member variable "running" is true.
///updats the game to a newer tick.
void game::tick(){
	no_of_agents=agent_list.size();
	if(running){
		for(int i=0;i<agent_list.size();i++){
			agent_list[i]->perform_actions();
		}

		add_newborn_agents_to_list();
		remove_dead_agents_from_list();
		if(agent_list.size()==0){
			running=false;
		}
		if(check_if_game_should_end()){
			running=false;
		}
		test_counter++;
	}
	print_board();
}

//print the Board
void game::print_board(){
	std::cout<<std::endl;
	std::cout<<std::endl;
	std::cout<<"("<<test_counter<<")"<<agent_list.size()<<std::endl;
	test_counter++;
	for(int i=0;i<board_obj->get_number_of_rows();i++){
		for(int j=0;j<board_obj->get_number_of_columns();j++){
			std::cout<<"|"<<board_obj->get_postion(i,j)<<"|";
		}
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
}

///creates a coyote at given position.
///Must only be called if the position is empty.
agent* game::create_coyote(int r,int c){
	agent_list.push_back(new coyote(r,c));
	board_obj->put_coyote(r,c);
}

///creates a roadrunner at given position.
///Must only be called if the position is empty.
agent* game::create_road_runner(int r,int c){
	agent_list.push_back(new roadrunner(r,c));
	board_obj->put_roadrunner(r,c);
}

///generates the given number of coyote inside the board.
///stops when or if there is no space left in the board.
void game::generate_random_coyotes(int number){
	int r,c;
	for(int i=0;i<number;i++){
		do{
			r=rand()%(board_obj->get_number_of_rows());
			c=rand()%(board_obj->get_number_of_columns());
			if (!(board_obj->is_there_free_cell())) {
				continue;
			}
		}while(!(board_obj->get_postion(r,c)==board_obj->get_empty_character()));
		create_coyote(r,c);
	}
}

///generates the given number of roadrunner inside the board.
///stops when or if there is no space left in the board.
void game::generate_random_roadrunners(int number){
	int r,c;
	for(int i=0;i<number;i++){
		do{
			r=rand()%(board_obj->get_number_of_rows());
			c=rand()%(board_obj->get_number_of_columns());
			if (!(board_obj->is_there_free_cell())) {
				continue;
			}
		}while(!(board_obj->get_postion(r,c)==board_obj->get_empty_character()));
		create_road_runner(r,c);
	}
}

///removes all the dead agents from the main list.
///must be called after every action to make sure dead stuff don't perform actions.
void game::remove_dead_agents_from_list(){
	for(int i=0;i<agent_list.size();i++){
		if(agent_list[i]->check_if_dead()){
			delete agent_list[i];
			agent_list.erase(agent_list.begin()+i);
			i--;
		}
	}
}

///adds all the newborn agents from the main list.
///must be called after every action to make sure no child is lost.
void game::add_newborn_agents_to_list(){
	for(int i=0;i<agent_list.size();i++){
		if(agent_list[i]->check_if_reproduced()){
			int r,c;
			agent_list[i]->give_child_position(r,c);
			if(agent_list[i]->get_agent_type()==board_obj->get_coyote_character()){
				create_coyote(r,c);
			}else if(agent_list[i]->get_agent_type()==board_obj->get_roadrunner_character()){
				create_road_runner(r,c);
			}
		}
	}
}

bool game::check_if_game_should_end(){
	if(agent_list.size()==0){
		return true;
	}
	for(int i=0;i<no_of_agents;i++){
		if(agent_list[i]->get_agent_type()==board_obj->get_coyote_character()){
			return false;
		}
	}
	return true;///game stops if there are no more coyotees or agents remaining.
}