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
	BONNIE_JUMPSCARE,
	CHICA_JUMPSCARE,
	FOXY_JUMPSCARE,
	GOLDEN_JUMPSCARE,
	GAME_OVER_STATIC,
	GAME_OVER_PIC,
	WIN,
	CONGRATS
};

enum DOOR_STATE {
	DOOR_STATE_IS_OPENING,
	DOOR_STATE_IS_CLOSING,
	DOOR_STATE_OPENED,
	DOOR_STATE_CLOSED
};

#define NUM_OF_SOUNDS 11

struct sounds_rooms {
	sound door;
	sound tab;
	sound nose;
	sound light_in_office;
	sound amb1;
	sound amb2;
	sound cam_reload;
	sound jumpscare1;
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
	sprite bonnie_jumpscare[10];
	sprite chica_jumpscare[16];
	sprite golden_jumpscare[20];
    sprite foxy_jumpscare[14];
	sprite golden_freddy;
	sprite cam_noize[8];
	sprite game_over;
	sprite win_5;
	sprite win_6;
	sprite win_am;
	sprite win_black;
    sprite attention;
    sprite small_att;
	sprite congr[3];
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
	ROOMS_STATE jumpscare;
	float tab_count;
	int AI_level[5];
	int fan_count;
	float time;
	float amb1_time;
	float time_until_next_blink;
	float in_office_time;
	float FPS;
	int blink_count;
	float jumpscare_count;
	float bonnie_time;
	bool bonnie_checked;
	float chica_time;
	bool chica_checked;
	float freddy_time;
	bool freddy_checked;
	float left_close_time;
	float right_close_time;
	int cam_noize_count;
	int number_of_night;
	float AI_lev;
	float golden_last_time;
	float golden_extra_time;
    float foxy_time_left;
	bool gf_blink;
	int gf_count;
	bool tab_sw;
	bool was_outside_of_switch_tab;
	bool left_button_on;
	bool right_button_on;
	bool light_in_office;
	bool nose_pressed;
	bool last_mlp;
};

extern std_obj_functions rooms_f;