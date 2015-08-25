#pragma once
#include "o_rooms.h"
#include "main_header.h"

struct sprites_camera {
	sprite map[2];
	sprite cam_item[2];
	sprite item_name[11];
	sprite glitches[11];
};

struct camera_data {
	sprites_camera sprites;
	v2i item_coord[11];
	float you_map_time;
	float cur_item_time;
	int cur;
	int glitch_count;
	bool you_big;
	bool cur_item_is_yellow;
};

void camera_init (rooms *rm);

void camera_update (float dt, rooms *rm, v2f m);

void camera_render (rooms *rm);

void camera_another_opening (rooms *rm);