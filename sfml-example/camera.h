#pragma once
#include "o_rooms.h"
#include "main_header.h"

struct sprites_camera {
	sprite map[2];
};

struct camera_data {
	sprites_camera sprites;
};

void camera_init (rooms *rm);

void camera_update (float dt, rooms *rm, v2f m);

void camera_render (rooms *rm);