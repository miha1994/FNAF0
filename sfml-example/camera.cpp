#include "camera.h"

void camera_init (rooms *rm) {
	camera_data *cam = rm->cam;
	sprites_camera *spr = &cam->sprites;
	spr->map[0].init ("assets/textures/map/145.png", 400,400);
	spr->map[0].itself.setPosition (854, 315);
	spr->map[1].init ("assets/textures/map/164.png", 400,400);
	spr->map[1].itself.setPosition (854, 315);
}

void camera_update (float dt, rooms *rm, v2f m) {
	if (m.x > 300 && m.x < 980 && m.y > 650) {
		if (rm->was_outside_of_switch_tab) {
			rm->state = ROOMS_STATE::TAB_TO_OFFICE;
			rm->tab_count = 10;
			rm->tab_sw = false;
			rm->sounds.tab.stop ();
			rm->sounds.tab.play ();
			return;
		}
	} else {
		rm->was_outside_of_switch_tab = true;
	}
	rm->db.text.setString (std::to_string (int(m.x)) + ", " + std::to_string (int(m.y)));
}

void camera_render (rooms *rm) {
	sprites_rooms *spr = &rm->sprites;
	sprite* spr1 = &rm->cam->sprites.map[0];
	spr1->draw (&window);
	if (rm->was_outside_of_switch_tab) {
		spr->switcher_to_camera.draw (&window);
	}
}