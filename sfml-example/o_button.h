#pragma once
#include <vector>
#include "object.h"
#include "sfml.h"
#include <list>
#include "some_structures.h"

struct r_button {
	r_button *prev;
	sprite *spr;
	r_button *next;
	bool is_current;
	bool is_active;
};

struct sprites_button {
	sprite title;
	sprite noize[8];
	sprite glitches[11];
	sprite background[4];
	sprite night[7];
	sprite new_game;
	sprite continue_;
	sprite sixth_night;
	sprite custom_night;
	sprite _20_mode[4];
	sprite pointer;
	sprite first_night;
	sprite black_screen;
	sprite loading;
	sprite star;
};

enum BUTTON_STATE {
	MENU,
	FIRST_NIGHT,
	SHOW_THE_NUMBER_OF_NIGHT
};

class button {
public:
	r_button buttons[4];
	sound theme;
	sound static_;
	sound item;
	sprites_button sprites;
	v2f prev_m_pos;
	int num_of_beaten_nigths;
	int choosed_night;
	int active_but;
	int noize_counter;
	int noize_r;
	int bg_counter1;
	int bg_counter2;
	int bg_r;
	int darkness_counter;
	int darkness_r;
	int darkness2_counter;
	int darkness2_r;
	int glitches_counter;
	int glitches_r;
	int num_of_20;
	BUTTON_STATE state;
	float static_glitch_shift;
	float first_night_time1;
	float first_night_time2;
	float show_the_number_of_nigth_time;
	bool prev_down;
	bool prev_up;
	bool exit;
}; 

extern std_obj_functions button_f;