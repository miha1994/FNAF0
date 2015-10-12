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
float volumes[26][2] = {{0,2.7f}, {0,3}, {0,4.2f}, 
{0,10},{25,12},{10,10},
{0,6},{0,7},{0,40},
{10,10},{2,5},{2,5},{2,5},
{10,10},{10,10},{10,10},{10,10},
{10,10},{10,10},{10,10},{10,10},
{0,4.6}, {0,4.6}, {0,4.6}, {0,4.6},{0,4.6}
};
int num_of_pic_for_room_watch[11];

float ____repeat = 0.07f;
bool ____last_value = false;

int bonnie_room, chica_room, freddy_room;
bool foxy_is_active;
int num_of_pic_4_room[11];

int ___tmp____[5] = {4,5,6,8,9};
int ___tmp0____[3] = {9,8,6};

void camera_render (rooms *rm) {
	sprites_rooms *spr = &rm->sprites;
	camera_data *cam = rm->cam;
	sprites_camera* cspr = &cam->sprites;
	sprite *ls = &cspr->rooms[number_of_png (rm, -1)];
	if (cam->cur != 4) {
		ls->itself.setPosition (-cam->shift, 0);
	}
	ls->draw (&window);
	bool hint_vis;
    if (cam->cur == 0 || cam->cur == 2) {
        v2f m;
        get_mouse_pos (m);
        int x = (m.x / 1280)*6;
        int y = (m.y / 720)*6;
		hint_vis = !(x < 4 && y > 1 && y < 4);
        FOR (i, 6) {
            FOR (j, 6) {
                if (i != x || j != y) {
                    cspr->dark_block.itself.setPosition ((1280.0/6)*i,(120)*j);
                    cspr->dark_block.draw (&window);
                }
            }
        }
        cspr->visible_block.itself.setPosition ((1280.0/6)*x - 10,(120)*y - 10);
        cspr->visible_block.draw (&window);
        if (rm->number_of_night == 1 || rm->time < 180) {
            cspr->info[5].draw (&window);
        }
    }
    if (cam->cur == 10 && cam->fg.is_on) {
        cspr->field.draw (&window);
        cspr->v[0].draw (&window);
        cspr->v[1].draw (&window);
        foxy_game *fg = &cam->fg;
        FOR (i, 32) {
            if (fg->field_array[i] < 2) {
                cspr->T[fg->field_array[i]].itself.setPosition (110 + (i % 8)*80, 174 + (i/8)*80);
                cspr->T[fg->field_array[i]].draw (&window);
            }
        }
		cspr->time[float_in_range (cam->fg.time_to_answer / cam->fg.tta5,1,5)].draw (&window);
		cspr->time[0].draw (&window);
    }
	if (cam->fg.great) {
		cspr->correct.draw (&window);
	}
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
    if (rm->foxy_time_left > 0) {
        if (rm->foxy_time_left < 5) {
            if ((int(rm->foxy_time_left * 4)) & 1) {
                rm->sprites.small_att.draw (&window);
            }
        } else if (rm->foxy_time_left < (rm->AI_level[FOXY] > 3 ? 10 : 25)) {
            if ((int(rm->foxy_time_left * 2)) & 1) {
                rm->sprites.small_att.draw (&window);
            }
        }
    }
	cspr->room_name[cam->cur].draw (&window);
	if (!cam->totc_stat && cam->cur < 9 && cam->cur > 3) {
		cspr->turn_on_the_camera.draw (&window);
		if (cam->cur != 10 && cam->cur != 7 && rm->number_of_night == 1) {
			cspr->info[0].draw (&window);
		}
	} else {
        if (cam->cur == 9 || cam->cur == 1 || cam->cur == 3) {
			cspr->camera_disabled_audio_only.draw (&window);
		}
	}
	if (rm->number_of_night > 1 && rm->number_of_night < 4) {
		if (cam->totc_stat == 0 && cam->cur != 10 && cam->cur != 7 && cam->cur > 3) {
			cspr->info[8].draw(&window);
		}
		int loc_a[4] = {9,6,10,7};
		if (cam->cur < 4) {
			if (!(cam->cur & 1)) {
				cspr->info[loc_a[cam->cur]].itself.setColor (sf::Color (255,255,255, hint_vis ? 255 : 100));
			}
			cspr->info[loc_a[cam->cur]].draw (&window);
		}
	} else if (rm->number_of_night == 4 || rm->number_of_night == 5) {
		if (cam->cur > 3 && cam->cur < 7) {
			cspr->info[11].draw (&window);
		} else if (cam->cur > 7 && cam->cur < 10) {
			cspr->info[12].draw (&window);
		} else if (cam->cur == 7 && rm->number_of_night == 5) {
			cspr->info[13].draw (&window);
		}
	}
	if (cam->totc_stat == 2 && rm->number_of_night < 4) {
		if (cam->cur != 10 && cam->cur != 7) {
			cspr->info[3].draw (&window);
		}
	}
	if (1);
	int st_o = -((int(rm->time*100))%200);
	FOR (i, 5) {
		cspr->dark.itself.setPosition (0, st_o + i * 200);
		cspr->dark.draw (&window);
	}
	if (rm->was_outside_of_switch_tab) {
		spr->switcher_to_camera.draw (&window);
	}
	if (cam->glitch_count-- > 0) {
		cspr->glitches[rand()%11].draw (&window);
	}

    //v2i m;
    //get_mouse_pos (m);
	/*
    rm->db.text.setString (std::to_string (cam->cur) + " " + std::to_string (0));
    window.draw (rm->db.text);
	*/
}