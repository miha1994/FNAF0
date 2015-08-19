#include "o_rooms.h"
#include "o_control.h"
#include "space.h"
#include "input.h"
#include "save.h"
#include "rooms_extra.h"
#include "office.h"
#include "camera.h"

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
		spr->right_door[i].itself.setTexture (spr->left_door[i].texture);
		spr->right_door[i].itself.setTextureRect (sf::Rect<int> (0,0,223,720));
		spr->right_door[i].itself.setScale (-1,1);
	}
	FOR (i, 11) {
		sprintf (str, "assets/textures/turning_on_the_camera/%d.png", i);
		spr->tablet[i].init (str, 1280, 720);
	}
	spr->switcher_to_camera.init ("assets/textures/other/420.png", 600, 60);
	spr->switcher_to_camera.itself.setOrigin (300, 30);
	spr->switcher_to_camera.itself.setPosition (640, 685);
	rm->cam = new camera_data;
	camera_init (rm);

	sounds_rooms *snd = &rm->sounds;
	snd->door.loadFromFile ("assets/snd/Door.wav",100);
	snd->tab.loadFromFile ("assets/snd/CAMERA_VIDEO_LOA_60105303.wav",100);

	rm->left_door_count = 0;
	rm->left_door_state = DOOR_STATE_OPENED;
	rm->right_door_count = 0;
	rm->right_door_state = DOOR_STATE_OPENED;

	spr->left_button_on.init ("assets/textures/office/124.png",92,247);
	spr->left_button_on.texture.setSmooth (false);

	spr->right_button_off.init ("assets/textures/office/134.png",92,247);
	spr->right_button_off.texture.setSmooth (false);
	
	spr->right_button_on.init ("assets/textures/office/135.png",92,247);
	spr->right_button_on.texture.setSmooth (false);
	rm->x_shift = 0;

	rm->db.font.loadFromFile ("assets/fonts/arial.ttf");
	rm->db.text.setFont (rm->db.font);

	rm->was_outside_of_switch_tab = false;

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
		office_update (dt, rm, m);
		break;
	case CAMERAS:
		camera_update (dt, rm, m);
		break;
	case TAB_TO_CAMERAS:
		if (rm->tab_sw) {
			++rm->tab_count;
		}
		rm->tab_sw = !rm->tab_sw;
		if (rm->tab_count == 11) {
			rm->state = CAMERAS;
			rm->was_outside_of_switch_tab = false;
		}
		break;
	case TAB_TO_OFFICE:
		if (rm->tab_sw) {
			--rm->tab_count;
		}
		rm->tab_sw = !rm->tab_sw;
		if (rm->tab_count < 0) {
			rm->state = IN_OFFICE;
			rm->was_outside_of_switch_tab = false;
			rm->sounds.tab.stop ();
		}
		break;
	}

	return false;
}

O_RENDER (rooms_render) {
	CNTRL ("rooms_render");
	O_DECL (rooms, rm);

	switch (rm->state) {
	case IN_OFFICE:
		office_render (rm);
		break;
	case CAMERAS:
		camera_render (rm);
		break;
	case TAB_TO_CAMERAS:
		office_render (rm);
		rm->sprites.tablet[rm->tab_count].draw (&window);
		break;
	case TAB_TO_OFFICE:
		office_render (rm);
		rm->sprites.tablet[rm->tab_count].draw (&window);
		break;
	}
	window.draw (rm->db.text);
}

O_DEL (rooms_del) {
	CNTRL ("rooms_del");
	O_DECL (rooms, rm);
	delete rm->cam;
	delete rm;
}

std_obj_functions rooms_f (rooms_load, rooms_update, rooms_render, rooms_del);