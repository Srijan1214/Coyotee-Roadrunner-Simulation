#include "coyote.h"

coyote::coyote(int r,int c):agent(r,c),no_of_moves_without_eating(0){
}

///Preforms all the actions that a coyote should do in every tick.
void coyote::perform_actions(){
	check_if_agent_should_die();
	has_reproduced=false;
	if(!dead){
		move();
		breed_if_possible();
	}
}

///Returns the unquie character representing the Coyote Agent.
char coyote::get_agent_type(){
	return board_obj->get_coyote_character();
}

///Kills off the coyote if conditions are satisfied.
///Here, coyote dies if it does not eat after the 4th clock cycle.
void coyote::check_if_agent_should_die() {
	if (no_of_moves_without_eating > 4) {
		this->dead = true;
		board_obj->put_empty(r, c);
	}
}
///Makes coyote move.
///Does nothing if no space available to move.
/*!
*If adjacent roadrunner is available to eat then go to that position to eat that roadrunner.
*If no roadrunner is at adjacent position, goes to a random possible direction.
*Simpler than roadrunner's movement
*/
void coyote::move(){
	if(is_roadrunner_atup(r,c)){
		move_up();
		eat();
	}else if(is_roadrunner_atdown(r,c)){
		move_down();
		eat();
	}else if(is_roadrunner_atleft(r,c)){
		move_left();
		eat();
	}else if(is_roadrunner_atright(r,c)){
		move_right();
		eat();
	}else{
		int direction;
		bool done_moving=false;
		int temp_r=r,temp_c=c;
		do{
			direction=rand()%4;
			switch(direction){
				case 0:
					move_up();
					break;
				case 1:
					move_down();
					break;
				case 2:
					move_left();
					break;
				case 3:
					move_right();
					break;
				default:
					break;
			}
			if(temp_r!=r || temp_c !=c){
				done_moving=true;
			}
			if((check_if_no_possible_moves(r,c))){
				done_moving=true;
			}
		}while(!done_moving);
	}
	no_of_moves_without_eating++;
	no_of_moves_since_birth++;
}

///Simply resets the coyote.
void coyote::eat(){
	no_of_moves_without_eating=0;
}

///Checks if there is a roadrunner above the given position parameters
///Parameters invalid if they are out of bounds and the function will return false
bool coyote::is_roadrunner_atup(int r,int c){
	if(board_obj->is_inside_bounds(r-1,c)){
		if(board_obj->get_postion(r-1,c)==board_obj->get_roadrunner_character()){
			return true;
		}
	}
	return false;
}

///Checks if there is a roadrunner below the given position parameters
///Parameters invalid if they are out of bounds and the function will return false
bool coyote::is_roadrunner_atdown(int r,int c){
	if(board_obj->is_inside_bounds(r+1,c)){
		if(board_obj->get_postion(r+1,c)==board_obj->get_roadrunner_character()){
			return true;
		}
	}
	return false;
}

///Checks if there is a roadrunner left of the given position parameters
///Parameters invalid if they are out of bounds and the function will return false
bool coyote::is_roadrunner_atleft(int r,int c){
	if(board_obj->is_inside_bounds(r,c-1)){
		if(board_obj->get_postion(r,c-1)==board_obj->get_roadrunner_character()){
			return true;
		}
	}
	return false;
}

///Checks if there is a roadrunner right of the given position parameters
///Parameters invalid if they are out of bounds and the function will return false
bool coyote::is_roadrunner_atright(int r,int c){
	if(board_obj->is_inside_bounds(r,c+1)){
		if(board_obj->get_postion(r,c+1)==board_obj->get_roadrunner_character()){
			return true;
		}
	}
	return false;
}

///Moves up if the next position is inside bounds.
///Does nothing if movement not possible.
void coyote::move_up(){
	if(board_obj->is_inside_bounds(r-1,c)){
		if(board_obj->get_postion(r-1,c)==board_obj->get_empty_character() || board_obj->get_postion(r-1,c)==board_obj->get_roadrunner_character()){
			board_obj->put_empty(r,c);
			r--;
			board_obj->put_coyote(r,c);
		}
	}
}

///Moves down if the next position is inside bounds.
///Does nothing if movement not possible.
void coyote::move_down(){
	if(board_obj->is_inside_bounds(r+1,c)){
		if(board_obj->get_postion(r+1,c)==board_obj->get_empty_character() || board_obj->get_postion(r+1,c)==board_obj->get_roadrunner_character()){
			board_obj->put_empty(r,c);
			r++;
			board_obj->put_coyote(r,c);
		}
	}
}

///Moves left if the next position is inside bounds.
///Does nothing if movement not possible.
void coyote::move_left(){
	if(board_obj->is_inside_bounds(r,c-1)){
		if(board_obj->get_postion(r,c-1)==board_obj->get_empty_character() || board_obj->get_postion(r,c-1)==board_obj->get_roadrunner_character()){
			board_obj->put_empty(r,c);
			c--;
			board_obj->put_coyote(r,c);
		}
	}
}

///Moves right if the next position is inside bounds.
///Does nothing if movement not possible.
void coyote::move_right(){
	if(board_obj->is_inside_bounds(r,c+1)){
		if(board_obj->get_postion(r,c+1)==board_obj->get_empty_character() || board_obj->get_postion(r,c+1)==board_obj->get_roadrunner_character()){
			board_obj->put_empty(r,c);
			c++;
			board_obj->put_coyote(r,c);
		}
	}
}

///Creates a child if the conditions for breading are statified.
void coyote::breed_if_possible(){
	if(no_of_moves_since_birth%8==0){
		do{
			child_r=rand()%(board_obj->get_number_of_rows());
			child_c=rand()%(board_obj->get_number_of_columns());
			if(!(board_obj->is_there_free_cell())){
				return;
			}
		}while(!(board_obj->get_postion(child_r,child_c)==board_obj->get_empty_character()));
		board_obj->put_coyote(child_r,child_c);
		has_reproduced=true;
	}
}

///Important function that checks if there is any space to make a move
bool coyote::check_if_no_possible_moves(int loc_r,int loc_c){
	if(board_obj->is_inside_bounds(loc_r-1,loc_c)){
	if(board_obj->get_postion(loc_r-1,loc_c)==board_obj->get_empty_character() || board_obj->get_postion(loc_r-1,loc_c)==board_obj->get_roadrunner_character()){
		return false;
	}
	}
	if(board_obj->is_inside_bounds(loc_r+1,loc_c)){
	if(board_obj->get_postion(loc_r+1,loc_c)==board_obj->get_empty_character()|| board_obj->get_postion(loc_r+1,loc_c)==board_obj->get_roadrunner_character()){
		return false;
	}
	}
	if(board_obj->is_inside_bounds(loc_r,loc_c-1)){
	if(board_obj->get_postion(loc_r,loc_c-1)==board_obj->get_empty_character()|| board_obj->get_postion(loc_r,loc_c-1)==board_obj->get_roadrunner_character()){
		return false;
	}
	}
	if(board_obj->is_inside_bounds(loc_r,loc_c+1)){
	if(board_obj->get_postion(loc_r,loc_c+1)==board_obj->get_empty_character()|| board_obj->get_postion(loc_r,loc_c+1)==board_obj->get_roadrunner_character()){
		return false;
	}
	}
	return true;
}
