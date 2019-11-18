#pragma once
#include "agent.h"

///The Coyote class
class coyote:public agent{
	public:
		coyote(int r,int c);
		void perform_actions() override;
		char get_agent_type() override;
		void give_child_position(int &r,int &c);
	private:
		void move();
		int no_of_moves_without_eating;
		bool is_roadrunner_atleft(int r,int c);
		bool is_roadrunner_atright(int r,int c);
		bool is_roadrunner_atup(int r,int c);
		bool is_roadrunner_atdown(int r,int c);
		bool check_if_no_possible_moves(int loc_r, int loc_c);
		void eat();
		void move_up();
		void move_down();
		void move_left();
		void move_right();
		void breed_if_possible();
	protected:
	void check_if_agent_should_die();
};
