///This is a singleton class
#include "board.h"

board* board::m_pInstance=NULL;

///Returns the current instance of the game board class.
board* board::Instance(int r,int c){
	if(!m_pInstance){
		m_pInstance=new board(r,c);
	}
	return m_pInstance;
}

///Sets the size of the board when first called.
board::board(int r,int c){
	game_board.resize(r);
	for(int i=0;i<r;i++){
		game_board[i].resize(c,EMPTY_CHAR);
	}
}

///Returns character representing free space.
char board::get_empty_character(){
	return EMPTY_CHAR;
}

///Returns character representing Coyote.
char board::get_coyote_character(){
	return COYOTE_CHAR;
}

///Returns character representing Roadrunner..
char board::get_roadrunner_character(){
	return ROAD_RUNNER_CHAR;
}

///Returns character of the given position. Parameters need to be within bounds.
char board::get_postion(int r,int c){
	return game_board[r][c];
}

///Returns number of rows of the board.
int board::get_number_of_rows(){
	return game_board.size();
}

///Returns number of columns of the board.
int board::get_number_of_columns(){
	return game_board[0].size();
}

///Puts a Coyote agent at given position. Parameters need to be within bounds.
void board::put_coyote(int r,int c){
	game_board[r][c]=COYOTE_CHAR;
}

///Puts a Roadrunner agent at given position. Parameters need to be within bounds.
void board::put_roadrunner(int r,int c){
	game_board[r][c]=ROAD_RUNNER_CHAR;
}

///Clears the given given position. Parameters need to be within bounds.
void board::put_empty(int r,int c){
	game_board[r][c]=EMPTY_CHAR;
}

///Checks if given position is inside the boards of the board.
bool board::is_inside_bounds(int r,int c){
	if(r<0 || r>=get_number_of_rows()){
		return false;
	}if(c<0 || c>=get_number_of_columns()){
		return false;
	}
	return true;
}

///Checks if there is any free cell remaining in the board.
bool board::is_there_free_cell(){
	for(int r=0;r<game_board.size();r++){
		for(int c=0;c<game_board[0].size();c++){
			if(game_board[r][c]==EMPTY_CHAR){
				return true;
			}
		}
	}
	return false;
}
