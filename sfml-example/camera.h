#pragma once
#include "o_rooms.h"
#include "main_header.h"
#include <map>

struct sprites_camera {
	sprite map[2];
	sprite cam_item[2];
	sprite item_name[11];
	sprite glitches[11];
	std::map <int, sprite> rooms;
	sprite room_name[11];
	sprite turn_on_the_camera;
	sprite camera_disabled_audio_only;
	sprite info[14];
    sprite dark_block;
    sprite visible_block;
    sprite field;
    sprite T[2];
    sprite v[2];
	sprite correct;
	sprite time[6];
	sprite dark;
};

struct sounds_camera {
	sound animatronic[26];
	sound wait;
};

enum WATCH_STATE {
	WATCH_RIGHT,
	WATCH_LEFT,
	WATCH_MOVING_TO_THE_RIGHT,
	WATCH_MOVING_TO_THE_LEFT
};

struct foxy_game {
    float time_to_answer;
	float tta5;
    bool is_on;
    int number_of_T0_squares;
    int T[2];
    int field_array[32];
	bool great;
};

struct camera_data {
	sprites_camera sprites;
	sounds_camera sounds;
	v2i item_coord[11];
	int sounds_in_room[11][3];
	float sounds_in_room_time[3];
	bool play[3];
    foxy_game fg;
	float you_map_time;
	float cur_item_time;
	float dt;
	int cur;
	float shift;
	WATCH_STATE w_s;
	float watch_time;
	int glitch_count;
	float totc_time;
	int totc_stat;
	bool you_big;
	bool cur_item_is_yellow;
};

void camera_init (rooms *rm);

void camera_update (float dt, rooms *rm, v2f m);

void camera_render (rooms *rm);

void camera_another_opening (rooms *rm);




extern int number_of_png (rooms *rm, int cam_cur);

extern int item_name_num[11];
extern int cam_watch_im_numbers[];
extern int array_names_of_rooms[11][3];
extern float volumes[26][2];
extern int num_of_pic_for_room_watch[11];

extern float ____repeat;
extern bool ____last_value;

extern int bonnie_room, chica_room, freddy_room;
extern bool foxy_is_active;
extern int num_of_pic_4_room[11];

extern int ___tmp____[5];
extern int ___tmp0____[3];