#include "agent.h"

agent::agent(int r,int c):board_obj(board::Instance(r,c)),r(r),c(c),dead(false),has_reproduced(false),no_of_moves_since_birth(0),
	child_r(__INT_MAX__),child_c(__INT_MAX__){
}

///Checks if the current agent is dead
bool agent::check_if_dead(){
	return dead;
}

///Copies the coordinates of newly generated child into the parameters
void agent::give_child_position(int &temp_r,int &temp_c){
	if(has_reproduced){
		temp_r=child_r;
		temp_c=child_c;
		child_r=__INT_MAX__;
		child_c==__INT_MAX__;
	}
}

///Check if the current agent has reproduced
bool agent::check_if_reproduced(){
	return has_reproduced;
}
