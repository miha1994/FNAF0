#include "camera.h"

int item_name_num[11] = {165, 172, 173, 169, 168, 174, 171, 170, 176, 175, 177};
int cam_watch_im_numbers[] = {188, 478, 479, 540, 571, 43, 44, 206, 49, 220, 451, 476, 486, 67, 221, 226, 487, 546, 554, 62, 190, 83, 205, 354, 555, 48, 90,
	120, 215, 222, 492, 1, 2, 19, 68, 223, 224, 355, 484, 41, 217, 219, 494, 66, 211, 338, 240, 553, 0};
int array_names_of_rooms[11][3] = {
	{76, 305, 26},
	{74, 192, 26},
	{75, 305, 26},
	{79, 192, 26},
	{50, 286, 26},
	{71, 195, 26},
	{72, 239, 26},
	{54, 217, 26},
	{77, 196, 26},
	{78, 151, 26},
	{70, 261, 28}
};
float volumes[26][2] = {{0,0.7f}, {0,1}, {0,1.2f}, 
{0,10},{25,12},{10,10},
{0,3},{0,3},{0,20},
{10,10},{10,10},{10,10},{10,10},
{10,10},{10,10},{10,10},{10,10},
{10,10},{10,10},{10,10},{10,10},
{0,1}, {0,1}, {0,1}, {0,1},{0,1}
};
int num_of_pic_for_room_watch[11];

float ____repeat = 0.07f;
bool ____last_value = false;

int bonnie_room, chica_room, freddy_room;
bool foxy_is_active;
int num_of_pic_4_room[11];

int number_of_png (rooms *rm, int cam_cur) {
	camera_data *cam = rm->cam;
	if (cam_cur < 0) {
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
			if (rand1 > 0.8) {
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
			if (rand1 > 0.8) {
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
			if (rand1 > 0.7) {
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

int ___tmp____[5] = {4,5,6,8,9};
int ___tmp0____[3] = {9,8,6};

void camera_another_opening (rooms *rm) {
	//FREDDY
	if (rm->time > 180 + (20 - rm->AI_level[FREDDY])*18) {
		freddy_room = ___tmp____[rand()%5];
	} else {
		freddy_room = 7;
	}
	//BONNIE
	if (freddy_room == 7 && (rm->time > (20 - rm->AI_level[BONNIE]) * 18) && (rand1 < 0.33)) {
		if (rand1 < 0.5) {
			bonnie_room = 0;
		} else {
			bonnie_room = 1;
		}
	}
	int bon_r;

	do {
		if (rm->AI_level[BONNIE] == 0) {
			bon_r = 2;
			break;
		}
		if (freddy_room != 7) {
			bon_r = 1;
			break;
		}
		if (rand1 > 0.8) {
			bon_r = 2;
		} else {
			if (rm->AI_level[BONNIE] < 5 && rm->time < 100) {
				bon_r = 2;
			}
			bon_r = 1;
		}
	} while (0);

	if (bon_r == 1) {
		do {
			bonnie_room = 4 + (rand ()%3);
		} while (bonnie_room == freddy_room);
	} else if (bon_r == 2) {
		bonnie_room = 7;
	}
	//CHICA
	if (freddy_room == 7 && (rm->time > (20 - rm->AI_level[CHICA]) * 18) && (bonnie_room > 1) && (rand1 < 0.5)) {
		if (rand1 < 0.5) {
			chica_room = 2;
		} else {
			chica_room = 3;
		}
	} 

	int ch_r;
	do {
		if (rm->AI_level[CHICA] == 0) {
			ch_r = 2;
			break;
		}
		if (freddy_room != 7) {
			ch_r = 1;
			break;
		}
		if (rand1 > 0.8) {
			ch_r = 2;
		} else {
			if (rm->AI_level[CHICA] < 5 && rm->time < 100) {
				ch_r = 2;
			}
			ch_r = 1;
		}
	} while (0);

	if (ch_r == 1) {
		do {
			chica_room = ___tmp0____[rand()%3];
		} while (chica_room == bonnie_room || chica_room == freddy_room);
	} else if (ch_r == 2) {
		chica_room = 7;
	}
	//FOXY
	if (rm->time > (20 - rm->AI_level[FOXY]) * 18) {
		foxy_is_active = rand1 > 0.6f;
	}
	//SAVE
	FOR (i, 11) {
		num_of_pic_4_room[i] = number_of_png (rm, i);
	}
	//SOUNDS
#define sir rm->cam->sounds_in_room
#define make_full_sound(sir_i)	if (rand () % 8 < 3) {sir_i[0] = rand ()%3;} else {sir_i[0] = 21 + rand () % 5;} sir_i[1] = 3 + rand () % 3;sir_i[2] = 6 + rand () % 3;
	FOR (i, 11) {
		FOR (j, 3) {
			sir[i][j] = -1;
		}
	}
	make_full_sound(sir[bonnie_room]);
	if (chica_room != 9) {
		make_full_sound(sir[chica_room]);
	} else {
		sir[9][2] = 13 + rand () % 2;
		sir[9][1] = 15 + rand () % 2;
	}
	if (sir[0][0] == -1 && sir[1][0] == -1 && (rm->time > (20 - rm->AI_level[BONNIE]) * 13)) {
		int tn = rand () % 2;
		make_full_sound(sir[tn]);
	}
	if (sir[2][0] == -1 && sir[3][0] == -1 && (rm->time > (20 - rm->AI_level[CHICA]) * 13)) {
		int tn = 2 + rand () % 2;
		make_full_sound(sir[tn]);
	}
	int ai_sum = 0;
	int ai_max = 0;
	FOR (i, 5) {
		ai_sum += rm->AI_level[i];
		if (rm->AI_level[i] > ai_max) {
			ai_max = rm->AI_level[i];
		}
	}

	FOR (i, 10) {
		if (sir[i][0] == -1 && sir[i][1] == -1 && sir[i][2] == -1) {
			if (ai_sum/5 < 4 && rm->time < 230) {
				if (rand1 > 0.9) {
					if(rand ()%14 < 9) {
						sir[i][1] = rand () % 9;
					} else {
						sir[i][1] = 21 + rand ()%5;
					}
				}
			} else if (ai_max < 10) {
				if (rand1 > 0.6) {
					sir[i][0] = 3 + rand () % 6;
				}
				if (rand1 > 0.7) {
					if (rand() % 8 < 3) {
						sir[i][2] = rand() % 3;
					} else {
						sir[i][2] = 21 + rand ()%5;
					}
				}
			} else {
				if (rand1 > 0.5) {
					sir[i][1] = 3 + rand () % 3;
					if (rand1 > 0.5) {
						sir[i][2] = (rand()%2) * 6 + rand () % 3;
					} else {
						sir[i][2] = 21 + rand () % 5;
					}
				}
			}
		}
	}

#undef sir
	rm->cam->sounds_in_room_time[0] = -2.0 - rand1;
	rm->cam->sounds_in_room_time[1] = - rand1*2;
	rm->cam->sounds_in_room_time[2] = -3.0 - rand1;
	FOR (z, 3) {
		rm->cam->play[z] = false;
	}
	//TOTC
	rm->cam->totc_time = 0.0f;
	rm->cam->totc_stat = 0;
}

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
	for (int *p = cam_watch_im_numbers; true; ++p) {
		sprintf (str, "assets/textures/camera/%d.png", *p);
		spr->rooms[*p].init (str, 1600, 720);
		spr->rooms[*p].itself.setColor (sf::Color(150,150,150,255));
		if (*p == 0) {
			break;
		}
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
	FOR (i, 11) {
		sprintf (str, "assets/textures/inscriptions/%d.png", array_names_of_rooms[i][0]);
		spr->room_name[i].init (str, array_names_of_rooms[i][1], array_names_of_rooms[i][2]);
		spr->room_name[i].itself.setPosition (836, 268);
	}
	spr->map[0].init ("assets/textures/map/145.png", 400,400);
	spr->map[0].itself.setPosition (854, 315);
	spr->map[1].init ("assets/textures/map/164.png", 400,400);
	spr->map[1].itself.setPosition (854, 315);
	spr->turn_on_the_camera.init ("assets/textures/other/481.png", 300, 100);
	spr->turn_on_the_camera.itself.setPosition (10,10);

	sound *snd = cam->sounds.animatronic;
	FOR (i, 3) {
		sprintf (str, "assets/snd/animatronic/bonnie_chica/music/%d.wav", i);
		snd[i].loadFromFile (str);
	}
	FOR (i, 3) {
		sprintf (str, "assets/snd/animatronic/bonnie_chica/steps/%d.wav", i);
		snd[3+i].loadFromFile (str);
	}
	FOR (i, 3) {
		sprintf (str, "assets/snd/animatronic/bonnie_chica/voice/%d.wav", i);
		snd[6+i].loadFromFile (str);
	}
	for (int i = 9; i < 26; ++i) {
		sprintf (str, "assets/snd/animatronic/%d.wav", i);
		snd[i].loadFromFile (str);
	}
	cam->sounds.wait.loadFromFile ("assets/snd/wait.wav");
	
	cam->watch_time = 1.f;
	cam->w_s = WATCH_LEFT;
	cam->shift = 0.f;
	cam->you_big = false;
	cam->you_map_time = 0.f;

	cam->cur_item_is_yellow = false;
	cam->cur_item_time = 0.f;

	cam->cur = 7;
}

void camera_update (float dt, rooms *rm, v2f m) {
	camera_data *cam = rm->cam;
	cam->dt = dt;
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
			FOR (k, 26) {
				rm->cam->sounds.animatronic[k].stop ();
			}
			return;
		}
	} else {
		rm->was_outside_of_switch_tab = true;
	}
	if (cam->totc_stat == 1) {
		if (!rm->sounds.static_.isPlaying ()) {
			cam->totc_stat = 2;
		}
	}
	if (mouse_left_pressed) {
		if (!cam->totc_stat && m.x >= 10 && m.x <= 310 && m.y >= 10 && m.y <= 110) {
			cam->totc_stat = 1;
			rm->sounds.static_.setVolume (50);
			rm->sounds.static_.play ();
		}
		FOR (i, 11) {
			if (sf::Rect <int> (cam->item_coord[i], v2i(60,40)).contains (v2i(m))) {
				if (cam->cur != i) {
					cam->cur_item_time = 0.0;
					cam->cur_item_is_yellow = false;
					cam->cur = i;
					rm->sounds.cam_reload.play ();
					cam->glitch_count = 5;
					rm->cam->sounds_in_room_time[0] = -2.0 - rand1;
					rm->cam->sounds_in_room_time[1] = - rand1*2;
					rm->cam->sounds_in_room_time[2] = -3.0 - rand1;
					FOR (k, 26) {
						rm->cam->sounds.animatronic[k].stop ();
					}
					FOR (z, 3) {
						rm->cam->play[z] = false;
					}
					cam->totc_time = 0.0f;
					cam->totc_stat = 0;
					rm->sounds.static_.stop ();
				}
				break;
			}
		}
	}
	FOR (i, 3) {
		int snd_num = cam->sounds_in_room[cam->cur][i];
		if (snd_num >= 0) {
			if ((cam->sounds_in_room_time[i]+=dt) >= 0) {
				if (!cam->sounds.animatronic[snd_num].isPlaying () && !cam->play[i]) {
					cam->sounds.animatronic[snd_num].play ();
					cam->play[i] = true;
				}
				cam->sounds.animatronic[snd_num].setVolume (
					(volumes[snd_num][0] + (volumes[snd_num][1]-volumes[snd_num][0]) * (cam->sounds_in_room_time[i] > 5 ? 1 : (cam->sounds_in_room_time[i]/5.0f)))
					* ((rm->time > 180) ? 1 + (rm->time - 180)/180.0f : 1));
			}
		}
	}
	cam->watch_time -= dt;
	switch (cam->w_s) {
	case WATCH_LEFT:
		if (cam->watch_time < 0) {
			cam->w_s = WATCH_MOVING_TO_THE_RIGHT;
		}
		break;
	case WATCH_RIGHT:
		if (cam->watch_time < 0) {
			cam->w_s = WATCH_MOVING_TO_THE_LEFT;
		}
		break;
	case WATCH_MOVING_TO_THE_LEFT:
		if ((cam->shift -= dt*40) < 0) {
			cam->shift = 0;
			cam->watch_time = 2.0f;
			cam->w_s = WATCH_LEFT;
		}
		break;
	case WATCH_MOVING_TO_THE_RIGHT:
		if ((cam->shift += dt*40) > 320) {
			cam->shift = 320;
			cam->watch_time = 2.0f;
			cam->w_s = WATCH_RIGHT;
		}
		break;
	}
	//rm->db.text.setString (std::to_string (int(cam->cur)));
	rm->db.text.setString (std::to_string (int(m.x)) + ", " + std::to_string (int(m.y)));
}

void camera_render (rooms *rm) {
	sprites_rooms *spr = &rm->sprites;
	camera_data *cam = rm->cam;
	sprites_camera* cspr = &cam->sprites;
	sprite *ls = &cspr->rooms[number_of_png (rm, -1)];
	if (cam->cur != 4) {
		ls->itself.setPosition (-cam->shift, 0);
	}
	ls->draw (&window);
	if (cam->totc_stat != 1) {
		spr->cam_noize[rm->cam_noize_count].itself.setColor (sf::Color (255,255,255,80));
	}
	spr->cam_noize[rm->cam_noize_count].draw (&window);
	spr->cam_noize[rm->cam_noize_count].itself.setColor (sf::Color (255,255,255,255));
	cspr->map[cam->you_big].draw (&window);
	FOR (i, 11) {
		int cam_item_num = (cam->cur == i) && cam->cur_item_is_yellow;
		cspr->cam_item[cam_item_num].itself.setPosition (v2f(cam->item_coord[i]));
		cspr->item_name[i].itself.setPosition (v2f(cam->item_coord[i]) + v2f(6,7));
		cspr->cam_item[cam_item_num].draw (&window);
		cspr->item_name[i].draw (&window);
	}
	cspr->room_name[cam->cur].draw (&window);
	if (!cam->totc_stat) {
		cspr->turn_on_the_camera.draw (&window);
	}
	if (rm->was_outside_of_switch_tab) {
		spr->switcher_to_camera.draw (&window);
	}
	if (cam->glitch_count-- > 0) {
		cspr->glitches[rand()%11].draw (&window);
	}
}