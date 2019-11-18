#pragma once 
#include "board.h"

///The Agent abstract class.
class agent{
	protected:
		board* board_obj;
		int r;
		int c;
		int child_r,child_c;
		int no_of_moves_since_birth;
		bool dead;
		bool has_reproduced;
		void check_if_agent_should_die();
	public:
		agent(int, int);
		virtual void perform_actions()=0;
		virtual char get_agent_type()=0;
		bool check_if_dead();
		bool check_if_reproduced();
		void give_child_position(int &r,int &c);
};
