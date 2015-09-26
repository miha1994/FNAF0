#include "camera.h"

void camera_update (float dt, rooms *rm, v2f m) {
	camera_data *cam = rm->cam;
	cam->dt = dt;
    if (rm->foxy_time_left < 0) {
        rm->state = FOXY_JUMPSCARE;
        rm->jumpscare = CAMERAS;
        rm->jumpscare_count = 0;
        rm->sounds.jumpscare1.play ();
    }
	rm->bonnie_time = 10.0f;
	rm->bonnie_checked = false;
	rm->chica_time = 8.5f;
	rm->chica_checked = false;
	rm->left_close_time = 0.0f;
	rm->right_close_time = 0.0f;
	if ((cam->you_map_time -= dt) < 0) {
		cam->you_map_time += 1.0f;
		cam->you_big = !cam->you_big;
	}
	if ((cam->cur_item_time -= dt) < 0) {
		cam->cur_item_time += 0.6f;
		cam->cur_item_is_yellow = !cam->cur_item_is_yellow;
	}
	if (cam->fg.is_on) {
		if ((cam->fg.time_to_answer -= dt) < 0) {
			rm->state = FOXY_JUMPSCARE;
			rm->jumpscare = CAMERAS;
			rm->jumpscare_count = 0;
			rm->sounds.jumpscare1.play ();
		}
	}
	if (m.x > 260 && m.x < 880 && m.y > 680) {
		if (rm->was_outside_of_switch_tab) {
			if (cam->fg.is_on) {
				rm->state = FOXY_JUMPSCARE;
				rm->jumpscare = CAMERAS;
				rm->jumpscare_count = 0;
				rm->sounds.jumpscare1.play ();
				rm->sounds.tab.stop ();
				rm->sounds.tab.play ();
			} else {
				rm->state = ROOMS_STATE::TAB_TO_OFFICE;
				rm->tab_count = 10;
				rm->tab_sw = false;
				rm->sounds.tab.stop ();
				rm->sounds.tab.play ();
				FOR (k, 26) {
					rm->cam->sounds.animatronic[k].stop ();
				}
				rm->sounds.static_.stop ();
				return;
			}
		}
	} else {
		rm->was_outside_of_switch_tab = true;
	}
	if (cam->totc_stat == 1) {
        if ((cam->totc_time+=dt) > 3.5f) {
            rm->sounds.static_.stop ();
			cam->totc_stat = 2;
		}
	}
    if (rm->foxy_time_left < (rm->AI_level[FOXY] > 3 ? 10 : 25) && cam->cur == 10) {
        rm->foxy_time_left = 10000;
        foxy_game *fg = &cam->fg;
        fg->is_on = true;
        fg->T[0] = rand()%2;
        fg->T[1] = !fg->T[0];
        fg->number_of_T0_squares = int((rm->AI_level[FOXY]+6) / 2) + rand()%4;
		fg->tta5 = (fg->time_to_answer = (20 - rm->AI_level[FOXY]) * (3.5f/ 20) + 0.5f + fg->number_of_T0_squares * 0.64) / 6;
        int n32[32];
        FOR (i, 32) {
            n32[i] = i;
            fg->field_array[i] = 2;
        }
        int l = 32, ch;
        FOR (i, fg->number_of_T0_squares) {
            fg->field_array[n32[ch = rand()%l]] = fg->T[0];
            n32[ch] = n32[--l];
        }
        FOR (i, fg->number_of_T0_squares-1) {
            fg->field_array[n32[ch = rand()%l]] = fg->T[1];
            n32[ch] = n32[--l];
        }
    }
	if (mouse_left_pressed) {
		if (cam->fg.is_on) {
			bool good;
			bool ch = false;
			if (sf::Rect <float> (cam->sprites.v[0].itself.getPosition(), v2f(640, 60)).contains(m)) {
				good = cam->fg.T[0];
				ch = true;
			} else if (sf::Rect <float> (cam->sprites.v[1].itself.getPosition(), v2f(640, 60)).contains(m)){
				good = cam->fg.T[1];
				ch = true;
			}
			if (ch) {
				if (!good) {
					rm->state = FOXY_JUMPSCARE;
					rm->jumpscare = CAMERAS;
					rm->jumpscare_count = 0;
					rm->sounds.jumpscare1.play ();
				} else {
					cam->fg.is_on = false;
					cam->fg.great = true;
				}
			}
		}
		if (cam->cur < 9 && cam->cur > 3 && !cam->totc_stat && m.x >= 10 && m.x <= 310 && m.y >= 10 && m.y <= 110) {
			cam->totc_stat = 1;
			rm->sounds.static_.setVolume (50);
			rm->sounds.static_.play ();
            cam->totc_time = 0.0f;
		}
		FOR (i, 11) {
			if (sf::Rect <int> (cam->item_coord[i], v2i(60,40)).contains (v2i(m))) {
				if (cam->cur != i) {
					cam->fg.great = false;
					if (cam->fg.is_on) {
						rm->state = FOXY_JUMPSCARE;
						rm->jumpscare = CAMERAS;
						rm->jumpscare_count = 0;
						rm->sounds.jumpscare1.play ();
						rm->sounds.cam_reload.play ();
					} 
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
	if (rm->time - rm->golden_last_time + rm->golden_extra_time > 60 + (20 - rm->AI_level[GOLDEN])*15) {
		rm->state = GOLDEN_JUMPSCARE;
		rm->jumpscare_count = 0;
		rm->sounds.jumpscare1.play ();
	}
}