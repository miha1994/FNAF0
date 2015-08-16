#include "rooms_extra.h"

float _x_array_1[3] = {80,220,400};
float _x_array_2[3] = {700,500,100};

float speed_of_camera_movement (float x) {
	if (x < _x_array_1[2]) {
		if (x < _x_array_1[1]) {
			if (x < _x_array_1[0]) {
				return -_x_array_2[0];
			}
			return -_x_array_2[1];
		}
		return -_x_array_2[2];
	}
	if (x > 1280 - _x_array_1[2]) {
		if (x > 1280 - _x_array_1[1]) {
			if (x > 1280 - _x_array_1[0]) {
				return _x_array_2[0];
			}
			return _x_array_2[1];
		}
		return _x_array_2[2];
	}
}