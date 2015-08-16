#include "input.h"
#include "main_header.h"

bool input_handler::light () {
	return kb::isKeyPressed (kb::LControl) || kb::isKeyPressed (kb::RControl);
}

int last_dir;

#define check(key,dir_num)	if (kb::isKeyPressed (key)) { \
		if (last_dir != dir_num) {	\
			*dir = dir_num;			\
			retval = true;			\
		}							\
		last_dir = dir_num;			\
	}

bool input_handler::get_direction (int *dir) {
	bool retval = false;
	check (kb::Up, 0)
	else check (kb::Right, 1)
	else check (kb::Down, 2)
	else check (kb::Left, 3)
	else {last_dir = 4;}
	return retval;
}

bool input_handler::exit_game () {
	return kb::isKeyPressed (kb::Escape);
}