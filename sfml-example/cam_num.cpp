#include "camera.h"

int number_of_png (rooms *rm, int cam_cur) {
	camera_data *cam = rm->cam;
	if (cam_cur < 0) {
        if (cam->cur == 0 || cam->cur == 2) {
            return num_of_pic_4_room[cam->cur];
        }
		if (rm->cam->totc_stat < 2) {
			return 1;
		}
		if (cam->cur == 1) {
			bool light;
			if ((____repeat -= cam->dt) > 0) {
				light = ____last_value;
			} else {
				light = rand1 > 0.5;
				____last_value = light;
				____repeat += 0.04f;
			}
			if (light) {
				return num_of_pic_4_room[1];
			}
			return 43;
		}
		return num_of_pic_4_room[cam->cur];
	}
	switch (cam_cur) {
	case 0:
		if (bonnie_room == 0) {
			if (rand1 > 0.33) {
				if (rand1 > 0.5) {
					return 478;
				} else {
					return 479;
				}
			} else {
				return 188;
			}
		}
		if (rand1 > 0.9) {
			return 571;
		}
		if (rand1 > 0.9) {
			return 540;
		}
		return 0;
	case 1:
		if (bonnie_room == 1) {
			return 206;
		}
		return 44;
	case 2:
		if (chica_room == 2) {
			if (rand1 > 0.33) {
				if (rand1 > 0.5) {
					return 451;
				} else {
					return 476;
				}
			} else {
				return 220;
			}
		}
		return 49;
	case 3:
		if (chica_room == 3) {
			if (rand1 > 0.5) {
				return 221;
			}
			return 226;
		}
		if (rand1 > 0.9) {
			return 554;
		}
		if (rand1 > 0.9) {
			return 546;
		}
		return 67;
	case 4:
		if (bonnie_room == 4) {
			return 190;
		}
		return 62;
	case 5:
		if (bonnie_room == 5) {
			if (rand1 > 0.6) {
				return 555;
			}
			return 205;
		}
		if (rand1 > 0.8) {
			return 354;
		}
		return 83;
	case 6:
		if (bonnie_room == 6) {
			if(rand1 > 0.5) {
				return 90;
			} else {
				return 120;
			}
		}
		if (chica_room == 6) {
			if(rand1 > 0.5) {
				return 215;
			} else {
				return 222;
			}
		}
		return 48;
	case 7:
		if (bonnie_room == 7 && chica_room == 7) {
			if (rand1 > 0.9) {
				return 2;
			}
			return 19;
		}
		if (bonnie_room == 7) {
			return 223;
		}
		if (chica_room == 7) {
			return 68;
		}
		if (freddy_room == 7) {
			if (rand1 > 0.7) {
				return 355;
			}
			return 224;
		}
		return 484;
	case 8:
		if (chica_room == 8) {
			if (rand1 > 0.6) {
				return 219;
			}
			return 217;
		}
		return 41;
	case 9:
		return 1;
	case 10:
		return 66;
	}
}
