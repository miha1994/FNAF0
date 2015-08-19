#pragma once
#include <vector>
#include "object.h"
#include "sfml.h"
#include "quad.h"
#include <list>
#include "some_structures.h"

enum ROOMS_STATE {
	IN_OFFICE,
	CAMERAS,
	TAB_TO_CAMERAS,
	TAB_TO_OFFICE
};

enum DOOR_STATE {
	DOOR_STATE_IS_OPENING,
	DOOR_STATE_IS_CLOSING,
	DOOR_STATE_OPENED,
	DOOR_STATE_CLOSED
};

struct sounds_rooms {
	sound door;
	sound tab;
};

struct sprites_rooms {
	sprite dark_office;
	sprite left_button_off;
	sprite left_button_on;
	sprite right_button_off;
	sprite right_button_on;
	sprite left_door[14];
	sprite right_door[14];
	sprite switcher_to_camera;
	sprite tablet[11];
};

struct debug_rooms {
	sf::Font font;
	sf::Text text;
};

struct enemy {
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
	int left_door_count;
	DOOR_STATE right_door_state;
	int right_door_count;
	ROOMS_STATE state;
	int tab_count;
	bool tab_sw;
	bool was_outside_of_switch_tab;
	bool left_button_on;
	bool right_button_on;
};

extern std_obj_functions rooms_f;