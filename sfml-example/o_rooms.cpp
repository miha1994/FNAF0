#include "o_rooms.h"
#include "o_control.h"
#include "space.h"
#include "input.h"
#include "save.h"
#include "rooms_extra.h"

O_LOAD (rooms_load) {
	CNTRL ("rooms_load");
	rooms *rm = new rooms;

	rm->state = IN_OFFICE;

	sprites_rooms *spr = &rm->sprites;
	spr->dark_office.init ("assets/textures/office/304.png", 1600, 720);
	spr->left_button_off.init ("assets/textures/office/122.png",92,247);
	spr->left_button_off.texture.setSmooth (false);
	char str[50];
	FOR (i, 14) {
		sprintf (str, "assets/textures/office/left_door/%d.png", i);
		spr->left_door[i].init (str, 223, 720);
		spr->left_door[i].texture.setSmooth (false);
		spr->left_door[i].itself.setPosition (40, 0);
	}
	rm->left_door_count = -1;
	rm->left_door_state = DOOR_STATE_OPENED;

	spr->left_button_on.init ("assets/textures/office/124.png",92,247);
	spr->left_button_on.texture.setSmooth (false);

	spr->right_button_off.init ("assets/textures/office/134.png",92,247);
	spr->right_button_off.texture.setSmooth (false);
	
	spr->right_button_on.init ("assets/textures/office/135.png",92,247);
	spr->right_button_on.texture.setSmooth (false);
	rm->x_shift = 0;

	rm->db.font.loadFromFile ("assets/fonts/arial.ttf");
	rm->db.text.setFont (rm->db.font);

	read_string ();
	return (char *)rm;
}

O_UPDATE (rooms_update) {
	CNTRL ("rooms_update");
	O_DECL (rooms, rm);

	v2f m;
	get_mouse_pos (m);
	switch (rm->state) {
	case IN_OFFICE:
		rm->x_shift += dt * speed_of_camera_movement (m.x);
		m.x += rm->x_shift;
		if (rm->x_shift > 320) {
			rm->x_shift = 320;
		} else if (rm->x_shift < 0) {
			rm->x_shift = 0;
		}
		//rm->db.text.setString (std::to_string (m.x) + ", " + std::to_string (m.y));
		if (mouse_left_pressed) {
			if (m.x >= 30 && m.x <= 68 && m.y >= 271 && m.y <= 327) {
				rm->left_button_on = true;
			} else {
				rm->left_button_on = false;
			}
			if (m.x >= 1532 && m.x <= 1570 && m.y >= 271 && m.y <= 327) {
				rm->right_button_on = true;
			} else {
				rm->right_button_on = false;
			}
		} else {
			rm->left_button_on = false;
			rm->right_button_on = false;
		}
		if (rm->left_button_on) {
			if (rm->left_door_count < 13) {
				rm->left_door_count++;
			}
		} else {
			if (rm->left_door_count > -1) {
				rm->left_door_count--;
			}
		}
		break;
	case CAMERAS:
		break;
	}

	return false;
}

O_RENDER (rooms_render) {
	CNTRL ("rooms_render");
	O_DECL (rooms, rm);

	switch (rm->state) {
	case IN_OFFICE:
		rm->sprites.dark_office.itself.setPosition (-rm->x_shift, 0);
		rm->sprites.dark_office.draw (&window);
		if (rm->left_button_on) {
			rm->sprites.left_button_on.itself.setPosition (0-rm->x_shift, 220);
			rm->sprites.left_button_on.draw (&window);
		} else {
			rm->sprites.left_button_off.itself.setPosition (0-rm->x_shift, 220);
			rm->sprites.left_button_off.draw (&window);
		}
		if (rm->right_button_on) {
			rm->sprites.right_button_on.itself.setPosition (1508-rm->x_shift, 220);
			rm->sprites.right_button_on.draw (&window);
		} else {
			rm->sprites.right_button_off.itself.setPosition (1508-rm->x_shift, 220);
			rm->sprites.right_button_off.draw (&window);
		}
		if (rm->left_door_count >= 0) {
			rm->sprites.left_door[rm->left_door_count].itself.setPosition (69 - rm->x_shift, 0);
			rm->sprites.left_door[rm->left_door_count].draw (&window);
		}
		break;
	case CAMERAS:
		break;
	}
	window.draw (rm->db.text);
}

O_DEL (rooms_del) {
	CNTRL ("rooms_del");
	O_DECL (rooms, rm);
	delete rm;
}

std_obj_functions rooms_f (rooms_load, rooms_update, rooms_render, rooms_del);