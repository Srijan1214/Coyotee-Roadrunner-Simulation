#include "roadrunner.h"
#include "board.h"

roadrunner::roadrunner(int r,int c):agent(r,c){
}

///Does all the actions that a roadrunner should do in every tick.
void roadrunner::perform_actions(){
	check_if_agent_should_die();
	has_reproduced=false;
	if(!dead){
		move();
		breed_if_possible();
	}
}

///Roadrunner moves one step to a random direction if there is no adjacent coyote .
///If there is an adjacent coyote, the roadrunner moves either 1 step, or 2 step depending on the minimum number of adjacent coyote.
///The most complex function in this project because of the sheer amounts of checking the roadrunner needs to do, before taking a step.
///Will do nothing if the roadrunner has no space to move.
void roadrunner::move(){
	int no_of_close_coyote=0;
	if(get_no_of_adjacent_coyote(r,c)==0){
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
			if(check_if_no_possible_moves(r,c)){
				done_moving=true;
			}
		}while(!done_moving);
	}else{
		move_in_a_calculated_direction();
	}
	no_of_moves_since_birth++;
}

///Checks if a coyote has already occupied the square it is sitting on.
///This should be called before every set of actions as we do not want the roadrunner to do anything if it is dead.
void roadrunner::check_if_agent_should_die(){
	if(board_obj->get_postion(r,c)==board_obj->get_coyote_character()){
		dead=true;
	}
}

///return the number of adcaject coyote from the given position
int roadrunner::get_no_of_adjacent_coyote(int r,int c){
	int count=0;
	if(is_coyote_atup(r,c)){
		count++;
	}
	if(is_coyote_atdown(r,c)){
		count++;
	}
	if(is_coyote_atleft(r,c)){
		count++;
	}
	if(is_coyote_atright(r,c)){
		count++;
	}

	return count;
}

///Checks if there is a coyote above the given position parameters
///Parameters invalid if they are out of bounds and the function will return false
bool roadrunner::is_coyote_atup(int r,int c){
	if(board_obj->is_inside_bounds(r-1,c)){
		if(board_obj->get_postion(r-1,c)==board_obj->get_coyote_character()){
			return true;
		}
	}
	return false;
}

///Checks if there is a coyote below the given position parameters
///Parameters invalid if they are out of bounds and the function will return false
bool roadrunner::is_coyote_atdown(int r,int c){
	if(board_obj->is_inside_bounds(r+1,c)){
		if(board_obj->get_postion(r+1,c)==board_obj->get_coyote_character()){
			return true;
		}
	}
	return false;
}

///Checks if there is a coyote left the given position parameters
///Parameters invalid if they are out of bounds and the function will return false
bool roadrunner::is_coyote_atleft(int r,int c){
	if(board_obj->is_inside_bounds(r,c-1)){
		if(board_obj->get_postion(r,c-1)==board_obj->get_coyote_character()){
			return true;
		}
	}
	return false;
}

///Checks if there is a coyote left the given position parameters
///Parameters invalid if they are out of bounds and the function will return false
bool roadrunner::is_coyote_atright(int r,int c){
	if(board_obj->is_inside_bounds(r,c+1)){
		if(board_obj->get_postion(r,c+1)==board_obj->get_coyote_character()){
			return true;
		}
	}
	return false;
}

///Moves up if the next position is inside bounds.
///Does nothing if movement not possible.
void roadrunner::move_up(){
	if(board_obj->is_inside_bounds(r-1,c)){
		if(board_obj->get_postion(r-1,c)==board_obj->get_empty_character()){
			board_obj->put_empty(r,c);
			r--;
			board_obj->put_roadrunner(r,c);
		}
	}
}

///Moves down if the next position is inside bounds.
///Does nothing if movement not possible.
void roadrunner::move_down(){
	if(board_obj->is_inside_bounds(r+1,c)){
		if(board_obj->get_postion(r+1,c)==board_obj->get_empty_character()){
			board_obj->put_empty(r,c);
			r++;
			board_obj->put_roadrunner(r,c);
		}
	}
}

///Moves left if the next position is inside bounds.
///Does nothing if movement not possible.
void roadrunner::move_left(){
	if(board_obj->is_inside_bounds(r,c-1)){
		if(board_obj->get_postion(r,c-1)==board_obj->get_empty_character()){
			board_obj->put_empty(r,c);
			c--;
			board_obj->put_roadrunner(r,c);
		}
	}
}

///Moves right if the next position is inside bounds.
///Does nothing if movement not possible.
void roadrunner::move_right(){
	if(board_obj->is_inside_bounds(r,c+1)){
		if(board_obj->get_postion(r,c+1)==board_obj->get_empty_character()){
			board_obj->put_empty(r,c);
			c++;
			board_obj->put_roadrunner(r,c);
		}
	}
}

///does all the computation for moving if there is no coyote in adjacent cell
void roadrunner::move_in_a_calculated_direction(){
	int first_step_direction=__INT_MAX__;
	int second_step_direction=__INT_MAX__;
	int min_no_of_coyote=__INT_MAX__;
	first_step_direction=find_best_adjacent_direction(r,c,min_no_of_coyote);
	if((second_step_direction=find_best_adjacent_direction(r+1,c,min_no_of_coyote))!=__INT_MAX__){
		first_step_direction=0;
	}
	if((second_step_direction=find_best_adjacent_direction(r-1,c,min_no_of_coyote))!=__INT_MAX__){
		first_step_direction=1;
	}
	if((second_step_direction=find_best_adjacent_direction(r,c-1,min_no_of_coyote))!=__INT_MAX__){
		first_step_direction=2;
	}
	if((second_step_direction=find_best_adjacent_direction(r,c+1,min_no_of_coyote))!=__INT_MAX__){
		first_step_direction=3;
	}
	switch(first_step_direction){
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
	switch(second_step_direction){
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
	no_of_moves_since_birth++;
}

///finds a movable direction with least number of coyote
int roadrunner::find_best_adjacent_direction(int loc_r,int loc_c,int &min_no_of_coyote){
	int direction=__INT_MAX__;
	if(board_obj->is_inside_bounds(loc_r-1,loc_c)){
		if(board_obj->get_postion(loc_r-1,loc_c)==board_obj->get_empty_character()){
			if(get_no_of_adjacent_coyote(loc_r-1,loc_c)<min_no_of_coyote){
				min_no_of_coyote=get_no_of_adjacent_coyote(loc_r-1,loc_c);
				direction=0;
			}
		}
	}
	if(board_obj->is_inside_bounds(loc_r+1,loc_c)){
		if(board_obj->get_postion(loc_r+1,loc_c)==board_obj->get_empty_character()){
			if(get_no_of_adjacent_coyote(loc_r+1,loc_c)<min_no_of_coyote){
				min_no_of_coyote=get_no_of_adjacent_coyote(loc_r+1,loc_c);
				direction=1;
			}
		}
	}
	if(board_obj->is_inside_bounds(loc_r,loc_c-1)){
		if(board_obj->get_postion(loc_r,loc_c-1)==board_obj->get_empty_character()){
			if(get_no_of_adjacent_coyote(loc_r,loc_c-1)<min_no_of_coyote){
				min_no_of_coyote=get_no_of_adjacent_coyote(loc_r,loc_c-1);
				direction=2;
			}
		}
	}
	if(board_obj->is_inside_bounds(loc_r,loc_c+1)){
		if(board_obj->get_postion(loc_r,loc_c+1)==board_obj->get_empty_character()){
			if(get_no_of_adjacent_coyote(loc_r,loc_c+1)<min_no_of_coyote){
				min_no_of_coyote=get_no_of_adjacent_coyote(loc_r,loc_c+1);
				direction=3;
			}
		}
	}
	return direction;
}

///returns the character 'C' which is gotten from the board class
char roadrunner::get_agent_type(){
	return board_obj->get_roadrunner_character();
}

///Creates a child if the conditions for breading are statified.
///Here, the condition is taking every 3rd step since birth.
void roadrunner::breed_if_possible(){
	if(no_of_moves_since_birth%3==0){
		do{
			child_r=rand()%board_obj->get_number_of_rows();
			child_c=rand()%board_obj->get_number_of_columns();
			if(!(board_obj->is_there_free_cell())){
				return;
			}
		}while(!(board_obj->get_postion(child_r,child_c)==board_obj->get_empty_character()));
		board_obj->put_roadrunner(child_r,child_c);
		has_reproduced=true;
	}
}

///Important function that checks if there is any space to make a move
bool roadrunner::check_if_no_possible_moves(int loc_r,int loc_c){
	if(board_obj->is_inside_bounds(loc_r-1,loc_c)){
		if(board_obj->get_postion(loc_r-1,loc_c)==board_obj->get_empty_character()){
			return false;
		}
	}
	if(board_obj->is_inside_bounds(loc_r+1,loc_c)){
		if(board_obj->get_postion(loc_r+1,loc_c)==board_obj->get_empty_character()){
			return false;
		}
	}
	if(board_obj->is_inside_bounds(loc_r,loc_c-1)){
		if(board_obj->get_postion(loc_r,loc_c-1)==board_obj->get_empty_character()){
			return false;
		}
	}
	if(board_obj->is_inside_bounds(loc_r,loc_c+1)){
		if(board_obj->get_postion(loc_r,loc_c+1)==board_obj->get_empty_character()){
			return false;
		}
	}
	return true;
}
