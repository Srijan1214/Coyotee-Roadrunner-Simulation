#pragma once
#include "agent.h"
#include "board.h"

///The Roadrunner class
class roadrunner: public agent{
	public:
		roadrunner(int r,int c);
		void perform_actions();
		void move();
		void give_child_position(int &r,int &c);
		char get_agent_type() override;
	private:
		bool is_coyote_atleft(int r,int c);
		bool is_coyote_atright(int r,int c);
		bool is_coyote_atup(int r,int c);
		bool is_coyote_atdown(int r,int c);
		int get_no_of_adjacent_coyote(int r,int c);
		void move_up();
		void move_down();
		void move_left();
		void move_right();
		void breed_if_possible();
		void move_in_a_calculated_direction();
		int find_best_adjacent_direction(int loc_r,int loc_c,int &);
		bool check_if_no_possible_moves(int loc_r,int loc_c);
		
	protected:
		void check_if_agent_should_die();
};
