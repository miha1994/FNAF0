#pragma once
#include <vector>
#include "object.h"
#include "sfml.h"
#include "quad.h"
#include <list>
#include "some_structures.h"

#define BONNIE		0
#define CHICA		1
#define FREDDY		2
#define FOXY		3
#define GOLDEN		4

int float_in_range (float v, int min, int max);

enum ROOMS_STATE {
	IN_OFFICE,
	CAMERAS,
	TAB_TO_CAMERAS,
	TAB_TO_OFFICE,
	FREDDY_JUMPSCARE,
	GAME_OVER_STATIC,
	GAME_OVER_PIC,
	WIN
};

enum DOOR_STATE {
	DOOR_STATE_IS_OPENING,
	DOOR_STATE_IS_CLOSING,
	DOOR_STATE_OPENED,
	DOOR_STATE_CLOSED
};

#define NUM_OF_SOUNDS 12

struct sounds_rooms {
	sound door;
	sound tab;
	sound nose;
	sound light_in_office;
	sound amb1;
	sound amb2;
	sound cam_reload;
	sound jumpscare1;
	sound jumpscare2;
	sound static_;
	sound game_over;
	sound win1;
	sound win2;

	sound *all_sounds[NUM_OF_SOUNDS];
};

struct sprites_rooms {
	sprite dark_office;
	sprite light_office;
	sprite fan[3];
	sprite left_button_off;
	sprite left_button_on;
	sprite right_button_off;
	sprite right_button_on;
	sprite left_door[14];
	sprite right_door[14];
	sprite switcher_to_camera;
	sprite tablet[11];
	sprite AM;
	sprite dd[10];
	sprite night;
	sprite blink;
	sprite freddy_jumpscare[28];
	sprite cam_noize[8];
	sprite game_over;
	sprite win_5;
	sprite win_6;
	sprite win_am;
	sprite win_black;
};

struct debug_rooms {
	sf::Font font;
	sf::Text text;
};

struct camera_data;

class rooms {
public:
	sprites_rooms sprites;
	sounds_rooms sounds;
	camera_data *cam;
	debug_rooms db;
	float x_shift;
	DOOR_STATE left_door_state;
	float left_door_count;
	DOOR_STATE right_door_state;
	float right_door_count;
	ROOMS_STATE state;
	float tab_count;
	int AI_level[5];
	int fan_count;
	float time;
	float amb1_time;
	float time_until_next_blink;
	float in_office_time;
	float FPS;
	int blink_count;
	float freddy_jumpscare_count;
	int cam_noize_count;
	int number_of_night;
	bool tab_sw;
	bool was_outside_of_switch_tab;
	bool left_button_on;
	bool right_button_on;
	bool light_in_office;
	bool nose_pressed;
	bool last_mlp;
};

extern std_obj_functions rooms_f;