#pragma once
#include <vector>
#include <iostream>

///This is a singleton class that represents what is going on in the position.
//*This class helps the agent with computations.
class board{
	public:
		static board* Instance(int r,int c);
		char get_empty_character();
		char get_coyote_character();
		char get_roadrunner_character();
		char get_postion(int r,int c);
		int get_number_of_rows();
		int get_number_of_columns();
		void put_coyote(int r,int c);
		void put_roadrunner(int r,int c);
		void put_empty(int r,int c);
		bool is_inside_bounds(int r,int c);
		bool is_there_free_cell();
	private:
		const char ROAD_RUNNER_CHAR='R';
		const char COYOTE_CHAR='C';
		const char EMPTY_CHAR='-';
		std::vector<std::vector<char>> game_board;
		board();
		board(int r,int c);
		board(board const&){};
		board& operator=(board const&);
		static board* m_pInstance;
};
