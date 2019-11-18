#pragma once
#include <vector>
#include "agent.h"
#include "coyote.h"
#include "roadrunner.h"
#include "board.h"

//The main game class.
///This composes of the list of agents and the game board.
class game{
	public:
		int test_counter;
		game(int,int,int,int);
		void tick();
		bool running;
		int no_of_agents;
	private:
		bool check_if_game_should_end();
		int no_of_rows;
		int no_of_columns;
		std::vector<agent*> agent_list;
		board* board_obj;
		void generate_random_roadrunners(int number);
		void generate_random_coyotes(int number);
		agent* create_coyote(int x,int y);
		agent* create_road_runner(int x, int y);
		void add_newborn_agents_to_list();
		void remove_dead_agents_from_list();
		void print_board();
};
