#include "camera.h"


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
		if (*p == 0) {
			break;
		}
	}
    spr->dark_block.init ("assets/textures/other/0.png", 216, 121);
    spr->visible_block.init ("assets/textures/other/1.png", 236, 141);
    spr->dark_block.itself.setColor (sf::Color::Black);
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
	spr->camera_disabled_audio_only.init ("assets/textures/inscriptions/42.png",371,54);
	spr->camera_disabled_audio_only.itself.setOrigin (371 / 2.0f, 0);
	spr->camera_disabled_audio_only.itself.setPosition (640, 12);
	spr->info[0].init ("assets/textures/inscriptions/info_0.png",705,300);
	spr->info[0].itself.setPosition (100, 450 - 150);
	spr->info[1].init ("assets/textures/inscriptions/info_1.png",435,214);
	spr->info[1].itself.setPosition (240, 360 - 107);
	spr->info[2].init ("assets/textures/inscriptions/info_2.png",435,214);
	spr->info[2].itself.setPosition (240, 360 - 107);
	spr->info[3].init ("assets/textures/inscriptions/info_3.png",519,99);
	spr->info[3].itself.setPosition (180, 360 - 50);
	spr->info[4].init ("assets/textures/inscriptions/info_4.png",527,41);
	spr->info[4].itself.setPosition (570 - 527/2.0f, 12);
    spr->info[5].init ("assets/textures/wtf/0.png", 319, 27);
    spr->info[5].itself.setPosition (640 - (319.0/2), 10);

    spr->field.init ("assets/textures/foxy_game/field.png", 640, 320);
    spr->field.itself.setPosition (110, 174);
    spr->T[0].init ("assets/textures/foxy_game/full.png", 80, 80);
    spr->T[1].init ("assets/textures/foxy_game/empty.png", 80, 80);
    spr->v[0].init ("assets/textures/foxy_game/v0.png", 640, 60);
    spr->v[0].itself.setPosition (110, 174 + 320 + 15);
    spr->v[1].init ("assets/textures/foxy_game/v1.png", 640, 60);
    spr->v[1].itself.setPosition (110, 174 + 320 + 90);
	spr->correct.init ("assets/textures/foxy_game/correct.png", 407, 83);
	spr->correct.itself.setPosition (380, 350-56);
	FOR (i, 6) {
		sprintf(str, "assets/textures/foxy_game/time%d.png", i);
		spr->time[i].init (str, 300, 140);
		spr->time[i].itself.setPosition (640-150, 20);
	}

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
    cam->fg.is_on = false;

	cam->cur = 7;
	bonnie_room = 7;
	chica_room = 7;
	freddy_room = 7;
	foxy_is_active = 0;
}