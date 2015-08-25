#include "camera.h"

int item_name_num[11] = {165, 172, 173, 169, 168, 174, 171, 170, 176, 175, 177};

void camera_init (rooms *rm) {
	camera_data *cam = rm->cam;
	sprites_camera *spr = &cam->sprites;

	cam->item_coord[0].x = 960; cam->item_coord[0].y = 625;
	cam->item_coord[1].x = 960; cam->item_coord[1].y = 576;
	cam->item_coord[2].x = 1066; cam->item_coord[2].y = 625;
	cam->item_coord[3].x = 1066; cam->item_coord[3].y = 576;
	cam->item_coord[4].x = 879; cam->item_coord[4].y = 566;
	cam->item_coord[5].x = 834; cam->item_coord[5].y = 419;
	cam->item_coord[6].x = 939; cam->item_coord[6].y = 392;
	cam->item_coord[7].x = 955; cam->item_coord[7].y = 334;
	cam->item_coord[8].x = 1172; cam->item_coord[8].y = 421;
	cam->item_coord[9].x = 1164; cam->item_coord[9].y = 551;
	cam->item_coord[10].x = 907; cam->item_coord[10].y = 471;

	char str[50];
	FOR (i, 2) {
		sprintf (str, "assets/textures/map/%d.png", 167 - i);
		spr->cam_item[i].init (str, 60, 40);
	}
	FOR (i, 11) {
		sprintf (str, "assets/textures/map/%d.png", item_name_num[i]);
		spr->item_name[i].init (str, 31, 25);
	}
	FOR (i,11) {
		sprintf (str, "assets/textures/cam_glitches/%d.png", i);
		spr->glitches[i].init (str, 1280, 720);
		spr->glitches[i].itself.setColor (sf::Color (255,255,255,255));
	}
	spr->map[0].init ("assets/textures/map/145.png", 400,400);
	spr->map[0].itself.setPosition (854, 315);
	spr->map[1].init ("assets/textures/map/164.png", 400,400);
	spr->map[1].itself.setPosition (854, 315);
	
	
	cam->you_big = false;
	cam->you_map_time = 0.f;

	cam->cur_item_is_yellow = false;
	cam->cur_item_time = 0.f;

	cam->cur = 7;
}

void camera_another_opening (rooms *rm) {
}

void camera_update (float dt, rooms *rm, v2f m) {
	camera_data *cam = rm->cam;
	if ((cam->you_map_time -= dt) < 0) {
		cam->you_map_time += 1.0f;
		cam->you_big = !cam->you_big;
	}
	if ((cam->cur_item_time -= dt) < 0) {
		cam->cur_item_time += 0.6f;
		cam->cur_item_is_yellow = !cam->cur_item_is_yellow;
	}
	if (m.x > 230 && m.x < 910 && m.y > 650) {
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
	if (mouse_left_pressed) {
		FOR (i, 11) {
			if (sf::Rect <int> (cam->item_coord[i], v2i(60,40)).contains (v2i(m))) {
				if (cam->cur != i) {
					cam->cur_item_time = 0.0;
					cam->cur_item_is_yellow = false;
					cam->cur = i;
					rm->sounds.cam_reload.play ();
					cam->glitch_count = 5;
				}
				break;
			}
		}
	}
	//rm->db.text.setString (std::to_string (int(cam->cur)));
	rm->db.text.setString (std::to_string (int(m.x)) + ", " + std::to_string (int(m.y)));
}

void camera_render (rooms *rm) {
	sprites_rooms *spr = &rm->sprites;
	camera_data *cam = rm->cam;
	sprites_camera* cspr = &cam->sprites;
	cspr->map[cam->you_big].draw (&window);
	FOR (i, 11) {
		int cam_item_num = (cam->cur == i) && cam->cur_item_is_yellow;
		cspr->cam_item[cam_item_num].itself.setPosition (v2f(cam->item_coord[i]));
		cspr->item_name[i].itself.setPosition (v2f(cam->item_coord[i]) + v2f(6,7));
		cspr->cam_item[cam_item_num].draw (&window);
		cspr->item_name[i].draw (&window);
	}
	if (rm->was_outside_of_switch_tab) {
		spr->switcher_to_camera.draw (&window);
	}
	if (cam->glitch_count-- > 0) {
		cspr->glitches[rand()%11].draw (&window);
	}
}