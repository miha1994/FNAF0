#include "o_rooms.h"
#include "o_control.h"
#include "space.h"
#include "input.h"
#include "save.h"
#include "rooms_extra.h"
#include "office.h"
#include "camera.h"

extern int night_sizes[7][2];
extern int Ch_Nght;
int current_night = 1;
/*
#define BONNIE		0
#define CHICA		1
#define FREDDY		2
#define FOXY		3
#define GOLDEN		4
*/
int AI_LEVELS[7][5] = {
	{ 0, 0, 1, 1, 1},
	{10,10, 1, 3,15},
	{20,20, 1, 8,16},
	{ 0, 0,20, 4,17},
	{20,20,10, 6,18},
	{20,20,12,12,19},
	{20,20,20,20,20}
};

int float_in_range (float v, int min, int max) {
	int l_min = Min (v, max);
	return Max (min, l_min);
}

void stop_all_sounds(rooms *rm) {
	FOR (i, NUM_OF_SOUNDS) {
		rm->sounds.all_sounds[i]->stop ();
	}
	FOR (i, 26) {
		rm->cam->sounds.animatronic[i].stop ();
	}
	rm->cam->sounds.wait.stop ();
}

O_LOAD (rooms_load) {
	CNTRL ("rooms_load");
	rooms *rm = new rooms;

	rm->state = IN_OFFICE;
	rm->FPS = 60;
	rm->last_mlp = false;
	rm->number_of_night = Ch_Nght;
	rm->gf_blink = false;

	sprites_rooms *spr = &rm->sprites;
	spr->dark_office.init ("assets/textures/office/304.png", 1600, 720);
	spr->light_office.init ("assets/textures/office/39.png", 1600, 720);
	spr->left_button_off.init ("assets/textures/office/122.png", 92, 247);
	spr->left_button_off.texture.setSmooth (false);
	spr->fan[0].init ("assets/textures/office/57.png",138,196);
	spr->fan[1].init ("assets/textures/office/59.png",137,196);
	spr->fan[2].init ("assets/textures/office/60.png",137,196);
	spr->game_over.init ("assets/textures/camera/358.png", 1280, 720);
	rm->fan_count = 0;
	spr->win_5.init ("assets/textures/inscriptions/350.png", 53, 72);
	spr->win_6.init ("assets/textures/inscriptions/351.png", 53, 72);
	spr->win_am.init ("assets/textures/inscriptions/352.png", 113, 72);
	spr->win_am.itself.setPosition (625, 312);
    spr->attention.init ("assets/textures/foxy_game/big.png", 63, 55);
    spr->attention.itself.setPosition (890, 656);
    spr->small_att.init ("assets/textures/foxy_game/sml.png", 37, 32);
    spr->small_att.itself.setPosition (918, 457);
	spr->win_black.init ("assets/textures/wtf/327.png", 1280, 720);
	spr->win_black.texture.setSmooth (false);
	spr->golden_freddy.init ("assets/textures/other/573.png", 541, 521);
	spr->golden_freddy.texture.setSmooth (false);
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
	FOR (i, 10) {
		sprintf (str, "assets/textures/inscriptions/dd%d.png", i);
		spr->dd[i].init (str,30,36);
	}
	FOR (i, 28) {
		sprintf (str, "assets/textures/jumpscares/freddy_2/%d.png", i);
		spr->freddy_jumpscare[i].init (str, 1600, 720);
	}
	FOR (i, 10) {
		sprintf (str, "assets/textures/jumpscares/bonnie/%d.png", i);
		spr->bonnie_jumpscare[i].init (str, 1600, 720);
	}
	FOR (i, 16) {
		sprintf (str, "assets/textures/jumpscares/chica/%d.png", i);
		spr->chica_jumpscare[i].init (str, 1600, 720);
	}
	FOR (i, 20) {
		sprintf (str, "assets/textures/jumpscares/freddy_1/%d.png", i);
		spr->golden_jumpscare[i].init (str, 1280, 720);
	}
    FOR (i, 14) {
        sprintf (str, "assets/textures/jumpscares/foxy_1/%d.png", i);
		spr->foxy_jumpscare[i].init (str, 1024, 720);
    }
	FOR (i, 8) {
		sprintf (str, "assets/textures/cam_noize/%d.png", i);
		spr->cam_noize[i].init (str, 1280, 720);
	}
	
		sprintf (str, "assets/textures/inscriptions/nights/%d.png", rm->number_of_night);
		sprite *s = &spr->night;
		s->texture.loadFromFile (str);
		s->itself.setTexture (s->texture);
		s->itself.setTextureRect (sf::Rect<int> (0,63,night_sizes[current_night-1][0],night_sizes[current_night-1][1] - 63));
		s->itself.setPosition (1152, 61);
		s->itself.setScale (0.4, 0.4);

	spr->blink.init ("assets/textures/wtf/326.png", 1280, 720);
	rm->blink_count = 0;
	rm->time_until_next_blink = 10.0 + rand1 * 10;
	spr->AM.init ("assets/textures/inscriptions/251.png",42, 26);
	spr->AM.itself.setPosition (1200,20);
	spr->switcher_to_camera.init ("assets/textures/other/420.png", 600, 60);
	spr->switcher_to_camera.itself.setOrigin (300, 30);
	spr->switcher_to_camera.itself.setPosition (570, 685);

	spr->left_button_on.init ("assets/textures/office/124.png",92,247);
	spr->left_button_on.texture.setSmooth (false);

	spr->right_button_off.init ("assets/textures/office/134.png",92,247);
	spr->right_button_off.texture.setSmooth (false);
	
	spr->right_button_on.init ("assets/textures/office/135.png",92,247);
	spr->right_button_on.texture.setSmooth (false);
	FOR (i, 3) {
		sprintf (str, "assets/textures/ending/%d.png", i);
		spr->congr[i].init (str, 1280, 720);
	}
	rm->cam = new camera_data;
	camera_init (rm);

	sounds_rooms *snd = &rm->sounds;
	snd->door.loadFromFile ("assets/snd/Door.wav",50);
	snd->all_sounds[0] = &snd->door;
	snd->tab.loadFromFile ("assets/snd/CAMERA_VIDEO_LOA_60105303.wav",50);
	snd->all_sounds[1] = &snd->tab;
	snd->nose.loadFromFile ("assets/snd/PartyFavorraspyPart_AC01__3.wav", 60);
	snd->all_sounds[2] = &snd->nose;
	snd->light_in_office.loadFromFile ("assets/snd/BallastHumMedium2.wav", 50);
	snd->light_in_office.snd[0].setLoop (true);
	snd->all_sounds[3] = &snd->light_in_office;
	snd->amb1.loadFromFile ("assets/snd/ColdPresc B.wav", 50);
	snd->all_sounds[4] = &snd->amb1;
	snd->amb2.loadFromFile ("assets/snd/EerieAmbienceLargeSca_MV005.wav", 100);
	snd->amb2.snd[0].setLoop (true);
	snd->all_sounds[5] = &snd->amb2;
	snd->cam_reload.loadFromFile ("assets/snd/blip3.wav", 50);
	snd->all_sounds[6] = &snd->cam_reload;
	snd->jumpscare1.loadFromFile ("assets/snd/animatronic/XSCREAM.wav", 100);
	snd->all_sounds[7] = &snd->jumpscare1;
	snd->static_.loadFromFile ("assets/snd/static.wav", 100);
	snd->all_sounds[8] = &snd->static_;
	snd->game_over.loadFromFile ("assets/snd/stare.wav", 100);
	snd->win1.loadFromFile ("assets/snd/chimes 2.wav",100);
	snd->all_sounds[9] = &snd->win1;
	snd->win2.loadFromFile ("assets/snd/CROWD_SMALL_CHIL_EC049202.wav",50);
	snd->all_sounds[10] = &snd->win2;

	rm->left_door_count = 0;
	rm->left_door_state = DOOR_STATE_OPENED;
	rm->right_door_count = 0;
	rm->right_door_state = DOOR_STATE_OPENED;

	rm->x_shift = 0;

	rm->light_in_office = false;
	rm->nose_pressed = false;
	rm->amb1_time = 0;

	rm->db.font.loadFromFile ("assets/fonts/arial.ttf");
	rm->db.text.setFont (rm->db.font);

	rm->bonnie_time = 0;
	rm->bonnie_checked = true;
	rm->chica_time = 0;
	rm->chica_checked = true;
	rm->left_close_time = 0.0f;
	rm->right_close_time = 0.0f;

    rm->foxy_time_left = 10000;
	rm->was_outside_of_switch_tab = false;
	rm->time = 0.0f;
	rm->in_office_time = 0;
	rm->cam_noize_count = 0;
	rm->jumpscare = IN_OFFICE;
	rm->golden_last_time = 0.0;
	rm->golden_extra_time = 0.0;
	rm->AI_lev = 0;
	FOR (i, 5) {
		rm->AI_lev += (rm->AI_level[i] = AI_LEVELS[rm->number_of_night-1][i])/5.0;
	}

	read_string ();
	return (char *)rm;
}

O_UPDATE (rooms_update) {
	CNTRL ("rooms_update");
	O_DECL (rooms, rm);
    if (rm->foxy_time_left > 1000 && rm->AI_level[FOXY]) {
        rm->foxy_time_left = 30 + (20 - rm->AI_level[FOXY]) * 5 + rand1 * (10 + (20 - rm->AI_level[FOXY]));
    }

	if (kb::isKeyPressed (kb::F)) {
		rm->FPS = 1.f / dt;
	}
	if (rm->state == WIN) {
		v2f m;
		get_mouse_pos (m);
		rm->time += dt;
		if (rm->time > 10) {
			if (rm->number_of_night > 4) {
				rm->sounds.win1.stop ();
				rm->cam->sounds.animatronic[1].setVolume (50);
				rm->cam->sounds.animatronic[1].play ();
				rm->state = CONGRATS;
				rm->time = 0;
				return false;
			} else {
				control *mc = (control *)main_control;
				mc->todo.push_back (instruction ("delete", "L0"));
				mc->todo.push_back (instruction ("load", "MENU"));
				mc->todo.push_back (instruction ("active", "MENU"));
			}
		}
		if (rm->time > 4.0f && rm->time < 5.0f && rm->sounds.win2.snd[0].getStatus () != sf::Sound::Playing) {
			rm->sounds.win2.play ();
		}
		if (rm->time < 1.0) {
			rm->sprites.win_5.itself.setPosition (530, 312);
			rm->sprites.win_6.itself.setPosition (530, 430);
		} else if (rm->time < 5) {
			rm->sprites.win_5.itself.setPosition (530, 312 - (430-312)* (rm->time - 1.0)/4.0);
			rm->sprites.win_6.itself.setPosition (530, 430 - (430-312)* (rm->time - 1.0)/4.0);
		} else {
			rm->sprites.win_6.itself.setPosition (530, 312);
		}
		rm->last_mlp = mouse_left_pressed;
		if (rm->blink_count != 12345678) {
			rm->blink_count = 12345678;
			int n;
			get_save_status (&n);
			if (rm->number_of_night > n) {
				set_save_status (rm->number_of_night);
			}
		}
		return false;
	}
	if (rm->state == CONGRATS) {
		rm->time += dt;
		if (rm->time > 20) {
			control *mc = (control *)main_control;
			mc->todo.push_back (instruction ("delete", "L0"));
			mc->todo.push_back (instruction ("load", "MENU"));
			mc->todo.push_back (instruction ("active", "MENU"));
		}
		return false;
	}
	rm->time += dt;
    rm->foxy_time_left -= dt;
	if (rm->state == CAMERAS ||
		rm->state == IN_OFFICE ||
		rm->state == TAB_TO_CAMERAS ||
		rm->state == TAB_TO_OFFICE) {
		if (rm->time < 180) {
			rm->sounds.amb2.setVolume (0);
		} else {
			rm->sounds.amb2.setVolume ( (rm->time - 180) * 5.0 / 18.0);
		}
		if (rm->sounds.amb2.snd[0].getStatus () != sf::Sound::Playing) {
			rm->sounds.amb2.play ();
		}
		if ((rm->amb1_time -= dt) < 0) {
			rm->sounds.amb1.play ();
			rm->amb1_time += 110;
		}
		if (rm->blink_count) {
			--rm->blink_count;
		} else {
			if ((rm->time_until_next_blink -= dt) < 0 || rm->time >=360) {
				rm->blink_count = 5;
				rm->time_until_next_blink = rand1 * 2.7f;
			}
		}
	}
	rm->cam_noize_count = (rm->cam_noize_count + 1) % 8;
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
			rm->tab_count += dt*60.0f;
		}
		rm->tab_sw = !rm->tab_sw;
		if (rm->tab_count > 11) {
			rm->state = CAMERAS;
			rm->was_outside_of_switch_tab = false;
			camera_another_opening (rm);
			rm->sounds.cam_reload.play ();
			rm->cam->glitch_count = 5;
		}
		break;
	case TAB_TO_OFFICE:
		if (rm->tab_sw) {
			rm->tab_count -= dt*60;
		}
		rm->tab_sw = !rm->tab_sw;
		if (rm->tab_count < 0) {
			rm->state = IN_OFFICE;
			rm->was_outside_of_switch_tab = false;
			rm->sounds.tab.stop ();
		}
		break;
	case FREDDY_JUMPSCARE:
		if ((rm->jumpscare_count += dt*25) >= 28) {
			rm->state = GAME_OVER_STATIC;
			stop_all_sounds(rm);
			rm->sounds.game_over.play ();
			rm->amb1_time = 0;
		}
		rm->x_shift += dt * speed_of_camera_movement (m.x);
		if (rm->x_shift > 320) {
			rm->x_shift = 320;
		} else if (rm->x_shift < 0) {
			rm->x_shift = 0;
		}
		rm->sprites.freddy_jumpscare[float_in_range(rm->jumpscare_count,0,27)].itself.setPosition(-rm->x_shift, 0);
		break;
	case BONNIE_JUMPSCARE:
		if ((rm->jumpscare_count += dt*25) >= 20) {
			rm->state = GAME_OVER_STATIC;
			stop_all_sounds (rm);
			rm->sounds.game_over.play ();
			rm->amb1_time = 0;
		}
		rm->x_shift += dt * speed_of_camera_movement (m.x);
		if (rm->x_shift > 320) {
			rm->x_shift = 320;
		} else if (rm->x_shift < 0) {
			rm->x_shift = 0;
		}
		rm->sprites.bonnie_jumpscare[float_in_range(rm->jumpscare_count,0,19)%10].itself.setPosition(-rm->x_shift, 0);
		break;
	case CHICA_JUMPSCARE:
		if ((rm->jumpscare_count += dt*25) >= 32) {
			rm->state = GAME_OVER_STATIC;
			stop_all_sounds (rm);
			rm->sounds.game_over.play ();
			rm->amb1_time = 0;
		}
		rm->x_shift += dt * speed_of_camera_movement (m.x);
		if (rm->x_shift > 320) {
			rm->x_shift = 320;
		} else if (rm->x_shift < 0) {
			rm->x_shift = 0;
		}
		rm->sprites.chica_jumpscare[float_in_range(rm->jumpscare_count,0,31)%16].itself.setPosition(-rm->x_shift, 0);
		break;
	case GOLDEN_JUMPSCARE:
		if ((rm->jumpscare_count += dt*25) >= 20) {
			rm->state = GAME_OVER_STATIC;
			stop_all_sounds (rm);
			rm->sounds.game_over.play ();
			rm->amb1_time = 0;
		}
		rm->x_shift = 0;
		rm->sprites.golden_jumpscare[float_in_range(rm->jumpscare_count,0,19)].itself.setPosition(0, 0);
		break;
    case FOXY_JUMPSCARE:
        if ((rm->jumpscare_count += dt*25) >= 14) {
			rm->state = GAME_OVER_STATIC;
			stop_all_sounds (rm);
			rm->sounds.game_over.play ();
			rm->amb1_time = 0;
		}
        if (rm->jumpscare == IN_OFFICE) {
            rm->x_shift += dt * speed_of_camera_movement (m.x);
		    if (rm->x_shift > 320) {
			    rm->x_shift = 320;
		    } else if (rm->x_shift < 0) {
			    rm->x_shift = 0;
		    }
        }
        rm->sprites.foxy_jumpscare[float_in_range(rm->jumpscare_count,0,13)].itself.setPosition(0, 0);
        rm->sprites.foxy_jumpscare[float_in_range(rm->jumpscare_count,0,13)].itself.setScale (1280 / 1024.0, 1);
        break;
	case GAME_OVER_STATIC:
		if ((rm->amb1_time+=dt) > 7.0f) {
			rm->state = GAME_OVER_PIC;
			rm->sounds.game_over.stop ();
		}
		break;
	case GAME_OVER_PIC:
		if (Global_Bool_Key_Pressed || sf::Mouse::isButtonPressed (sf::Mouse::Left)|| sf::Mouse::isButtonPressed (sf::Mouse::Right)) {
			control *mc = (control *)main_control;
			mc->todo.push_back (instruction ("delete", "L0"));
			mc->todo.push_back (instruction ("load", "MENU"));
			mc->todo.push_back (instruction ("active", "MENU"));
		}
		break;
	}

	rm->last_mlp = mouse_left_pressed;
	return false;
}

O_RENDER (rooms_render) {
	CNTRL ("rooms_render");
	O_DECL (rooms, rm);

	sprites_rooms *spr = &rm->sprites;

	bool render_std = false;
	int tmp;
	switch (rm->state) {
	case IN_OFFICE:
		office_render (rm);
		render_std = true;
		break;
	case CAMERAS:
		camera_render (rm);
		render_std = true;
		break;
	case TAB_TO_CAMERAS:
		office_render (rm);
		rm->sprites.tablet[float_in_range (rm->tab_count, 0, 10)].draw (&window);
		render_std = true;
		break;
	case TAB_TO_OFFICE:
		office_render (rm);
		rm->sprites.tablet[float_in_range (rm->tab_count, 0, 10)].draw (&window);
		render_std = true;
		break;
	case FREDDY_JUMPSCARE:
		rm->sprites.freddy_jumpscare[float_in_range(rm->jumpscare_count,0,27)].draw (&window);
		break;
	case BONNIE_JUMPSCARE:
		tmp = float_in_range(rm->jumpscare_count,0,19);
		rm->sprites.bonnie_jumpscare[tmp%10].draw (&window);
		if (tmp < 5) {
			spr->blink.itself.setColor (sf::Color (255,255,255, 255 - tmp * 50));
			spr->blink.draw (&window);
		}
		break;
	case CHICA_JUMPSCARE:
		tmp = float_in_range(rm->jumpscare_count,0,31);
		rm->sprites.chica_jumpscare[tmp%16].draw (&window);
		if (tmp < 5) {
			spr->blink.itself.setColor (sf::Color (255,255,255, 255 - tmp * 50));
			spr->blink.draw (&window);
		}
		break;
	case GOLDEN_JUMPSCARE:
		tmp = float_in_range(rm->jumpscare_count,0,19);
		rm->sprites.golden_jumpscare[tmp].draw (&window);
		if (tmp < 5) {
			spr->blink.itself.setColor (sf::Color (255,255,255, 255 - tmp * 50));
			spr->blink.draw (&window);
		}
		break;
    case FOXY_JUMPSCARE:
        if (rm->jumpscare == IN_OFFICE) {
            office_render (rm);
        } else if (rm->jumpscare == CAMERAS) {
            camera_render (rm);
        }
        tmp = float_in_range(rm->jumpscare_count, 0, 13);
        rm->sprites.foxy_jumpscare[tmp].draw (&window);
        break;
	case GAME_OVER_STATIC:
		spr->cam_noize[rm->cam_noize_count].itself.setColor (sf::Color::White);
		spr->cam_noize[rm->cam_noize_count].draw (&window);
		break;
	case GAME_OVER_PIC:
		spr->game_over.draw (&window);
		break;
	case WIN:
		spr->win_5.draw (&window);
		spr->win_6.draw (&window);
		spr->win_am.draw (&window);
		spr->win_black.draw (&window);
		if (rm->time > 9) {
			spr->blink.itself.setColor (sf::Color (255,255,255, std::min(rm->time-9.0, 1.0) * 255));
			spr->blink.draw (&window);
		}
		break;
	case CONGRATS:
		spr->congr[rm->number_of_night - 5].draw (&window);
		if (rm->time < 1) {
			spr->blink.itself.setColor (sf::Color (255,255,255, (1 - rm->time) * 255));
			spr->blink.draw (&window);
		}
		if (rm->time > 19) {
			spr->blink.itself.setColor (sf::Color (255,255,255, std::min(rm->time-19.0, 1.0) * 255));
			spr->blink.draw (&window);
		}
	default:
		break;
	}
	if (render_std) {
		int am = floor (rm->time/60.0f);
		sprites_rooms *spr = &rm->sprites;

		if (rm->blink_count) {
			if (rm->blink_count == 3) {
				if (am >= 6) {
					rm->state = WIN;
					stop_all_sounds (rm);
					rm->time = 0;
					rm->sounds.win1.play ();
				}
				if (rm->jumpscare != IN_OFFICE) {
					rm->state = rm->jumpscare;
					rm->jumpscare_count = 0;
					rm->sounds.jumpscare1.play ();
				}
			}
			float force = fabs (float(3) - rm->blink_count);
			spr->blink.itself.setColor (sf::Color (255,255,255,255 - force * 85));
			spr->blink.draw (&window);
		}

		if (am) {
			spr->dd[am].itself.setPosition (1168, 20);
			float scl = 13/18.0;
			spr->dd[am].itself.setScale (scl, scl);
			spr->dd[am].draw (&window);
		} else {
			spr->dd[1].itself.setPosition (1148, 20);
			float scl = 13/18.0;
			spr->dd[1].itself.setScale (scl, scl);
			spr->dd[1].draw (&window);
			spr->dd[2].itself.setPosition (1168, 20);
			spr->dd[2].itself.setScale (scl, scl);
			spr->dd[2].draw (&window);
		}

		rm->sprites.AM.draw (&window);
		rm->sprites.night.draw (&window);

		rm->db.text.setString (rm->db.text.getString () + "\n" + std::to_string (int(rm->time)) + "\n" + std::to_string (int(rm->FPS)));
	}
    /*
    v2i m;
    get_mouse_pos (m);
    rm->db.text.setString (std::to_string (m.x) + " " + std::to_string (m.y));
    window.draw (rm->db.text);
    */
}

O_DEL (rooms_del) {
	CNTRL ("rooms_del");
	O_DECL (rooms, rm);
	delete rm->cam;
	delete rm;
}

std_obj_functions rooms_f (rooms_load, rooms_update, rooms_render, rooms_del);