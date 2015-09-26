#include "office.h"
#include "o_rooms.h"
#include "rooms_extra.h"
#include "camera.h"

void office_update (float dt, rooms *rm, v2f m) {
	rm->in_office_time += dt;
	rm->bonnie_time -= dt;
	rm->chica_time -= dt;
	rm->light_in_office = kb::isKeyPressed (kb::LControl) || kb::isKeyPressed (kb::RControl);
	if (rm->light_in_office) {
		if (rm->sounds.light_in_office.snd[0].getStatus() != sf::Sound::Playing) {
			rm->sounds.light_in_office.play ();
		}
		if (!rm->gf_blink && (rm->time - rm->golden_last_time + rm->golden_extra_time > 32 + (20 - rm->AI_level[GOLDEN])*8)) {
			rm->gf_blink = true;
			rm->gf_count = 0;
		}
	} else {
		if (rm->sounds.light_in_office.snd[0].getStatus() == sf::Sound::Playing) {
			rm->sounds.light_in_office.stop ();
		}
		rm->gf_blink = false;
	}
	if (rm->gf_blink) {
		rm->gf_count++;
		if (rm->gf_count > 60) {
			rm->gf_blink = false;
			rm->golden_last_time = rm->time;
			rm->golden_extra_time = 0;
		}
	}
	rm->x_shift += dt * speed_of_camera_movement (m.x);
	rm->db.text.setString (std::to_string (int(speed_of_camera_movement (m.x))));
	if (rm->x_shift > 320) {
		rm->x_shift = 320;
	} else if (rm->x_shift < 0) {
		rm->x_shift = 0;
	}
	if (m.x > 230 && m.x < 910 && m.y > 650) {
		if (rm->was_outside_of_switch_tab && rm->left_door_state == DOOR_STATE_OPENED && rm->right_door_state == DOOR_STATE_OPENED && !rm->light_in_office) {
			rm->state = ROOMS_STATE::TAB_TO_CAMERAS;
			rm->sounds.tab.play ();
			rm->tab_count = 0;
			rm->tab_sw = false;
			rm->light_in_office = false;
			rm->in_office_time = 0;
			if (!rm->bonnie_checked) {
				if (bonnie_room != 7) {
					if (!(bool(bonnie_room < 2) ^ bool (rm->left_close_time < 3))) {
						rm->jumpscare = BONNIE_JUMPSCARE;
					}
				}
				rm->bonnie_checked = true;
			}
			if (!rm->chica_checked) {
				if (chica_room != 7) {
					if (!(bool(chica_room < 4) ^ bool (rm->right_close_time < 3))) {
						rm->jumpscare = CHICA_JUMPSCARE;
					}
				}
				rm->bonnie_checked = true;
			}
			return;
		}
	} else {
		rm->was_outside_of_switch_tab = true;
	}
	if (rm->blink_count == 2) {
		if (rm->in_office_time > 100 - 4.2f * rm->AI_level[FREDDY]) {
			rm->state = FREDDY_JUMPSCARE;
			rm->jumpscare_count = 0;
			rm->sounds.jumpscare1.play ();
		}
		if (!rm->bonnie_checked && rm->bonnie_time < 0) {
			if (bonnie_room != 7) {
				if (!(bool(bonnie_room < 2) ^ bool (rm->left_close_time < 3))) {
					rm->state = BONNIE_JUMPSCARE;
					rm->jumpscare_count = 0;
					rm->sounds.jumpscare1.play ();
				}
			}
			rm->bonnie_checked = true;
		}
		if (!rm->chica_checked && rm->chica_time < 0) {
			if (chica_room != 7) {
				if (!(bool(chica_room < 4) ^ bool (rm->right_close_time < 3))) {
					rm->state = CHICA_JUMPSCARE;
					rm->jumpscare_count = 0;
					rm->sounds.jumpscare1.play ();
				}
			}
			rm->bonnie_checked = true;
		}
	}
	m.x += rm->x_shift;
	if (mouse_left_pressed && (sf::Rect <float> (675, 236, 8, 4).contains (m))) {
		if (!rm->nose_pressed) {
			rm->sounds.nose.play ();
			rm->nose_pressed = true;
		}
	} else {
		rm->nose_pressed = false;
	}
	if (rm->left_button_on) {// y > 650      300 < x < 980
		if (!(m.x >= 30 && m.x <= 68 && m.y >= 271 && m.y <= 327) || !mouse_left_pressed) {
			rm->left_button_on = false;
		}
	} else if (!rm->last_mlp && mouse_left_pressed && (m.x >= 30 && m.x <= 68 && m.y >= 271 && m.y <= 327)) {
		rm->left_button_on = true;
	}
	if (rm->right_button_on) {
		if (!(m.x >= 1532 && m.x <= 1570 && m.y >= 271 && m.y <= 327) || !mouse_left_pressed) {
			rm->right_button_on = false;
		}
	} else if (!rm->last_mlp && mouse_left_pressed && (m.x >= 1532 && m.x <= 1570 && m.y >= 271 && m.y <= 327)) {
		rm->right_button_on = true;
	}
	switch (rm->left_door_state) {
	case DOOR_STATE_OPENED:
		if (rm->left_button_on) {
			rm->left_door_state = DOOR_STATE_IS_CLOSING;
			rm->left_door_count = 0;
			rm->sounds.door.play ();
		}
		break;
	case DOOR_STATE_CLOSED:
		if (!rm->left_button_on) {
			rm->left_door_state = DOOR_STATE_IS_OPENING;
			rm->left_door_count = 13;
			rm->sounds.door.play ();
		}
		rm->left_close_time += dt;
		break;
	case DOOR_STATE_IS_OPENING:
		if (rm->left_door_count <= 0) {
			rm->left_door_state = DOOR_STATE_OPENED;
		} else {
			rm->left_door_count -= dt*45.f;
		}
		rm->left_button_on = false;
		break;
	case DOOR_STATE_IS_CLOSING:
		if (rm->left_door_count >= 13) {
			rm->left_door_state = DOOR_STATE_CLOSED;
		} else {
			rm->left_door_count += dt*45.f;
		}
		rm->left_button_on = true;
		break;
	}
	switch (rm->right_door_state) {
	case DOOR_STATE_OPENED:
		if (rm->right_button_on) {
			rm->right_door_state = DOOR_STATE_IS_CLOSING;
			rm->right_door_count = 0;
			rm->sounds.door.play ();
		}
		break;
	case DOOR_STATE_CLOSED:
		if (!rm->right_button_on) {
			rm->right_door_state = DOOR_STATE_IS_OPENING;
			rm->right_door_count = 13;
			rm->sounds.door.play ();
		}
		rm->right_close_time += dt;
		break;
	case DOOR_STATE_IS_OPENING:
		if (rm->right_door_count <= 0) {
			rm->right_door_state = DOOR_STATE_OPENED;
		} else {
			rm->right_door_count -= dt*45.f;
		}
		rm->right_button_on = false;
		break;
	case DOOR_STATE_IS_CLOSING:
		if (rm->right_door_count >= 13) {
			rm->right_door_state = DOOR_STATE_CLOSED;
		} else {
			rm->right_door_count += dt * 45.f;
		}
		rm->right_button_on = true;
		break;
	}
	if (rm->time - rm->golden_last_time + rm->golden_extra_time > 60 + (20 - rm->AI_level[GOLDEN])*15) {
		rm->state = GOLDEN_JUMPSCARE;
		rm->jumpscare_count = 0;
		rm->sounds.jumpscare1.play ();
	}
    if (rm->foxy_time_left < 0) {
        rm->state = FOXY_JUMPSCARE;
        rm->jumpscare = IN_OFFICE;
        rm->jumpscare_count = 0;
        rm->sounds.jumpscare1.play ();
    }
}

void office_render (rooms *rm) {
	if (rm->light_in_office) {
		rm->sprites.light_office.itself.setPosition (-rm->x_shift, 0);
		rm->sprites.light_office.draw (&window);
		rm->sprites.fan[rm->fan_count].draw (&window, true, v2f(780-rm->x_shift,303));
		if ((++rm->fan_count) > 2) {
			rm->fan_count = 0;
		}
		if (rm->gf_blink) {
			rm->sprites.golden_freddy.itself.setPosition (380 - rm->x_shift, 220);
			rm->sprites.golden_freddy.draw (&window);
		}
	} else {
		rm->sprites.dark_office.itself.setPosition (-rm->x_shift, 0);
		rm->sprites.dark_office.draw (&window);
	}
	if (rm->left_door_state != DOOR_STATE_OPENED) {
		rm->sprites.left_door[float_in_range (rm->left_door_count,0,13)].itself.setPosition (68-rm->x_shift, 0);
		rm->sprites.left_door[float_in_range (rm->left_door_count,0,13)].draw (&window);
	}
	if (rm->right_door_state != DOOR_STATE_OPENED) {
		rm->sprites.right_door[float_in_range (rm->right_door_count,0,13)].itself.setPosition (1498-rm->x_shift, 0);
		rm->sprites.right_door[float_in_range (rm->right_door_count,0,13)].draw (&window);
	}
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
	if (rm->was_outside_of_switch_tab && !rm->light_in_office) {
		rm->sprites.switcher_to_camera.draw (&window);
	}
    if (rm->foxy_time_left > 0) {
        if (rm->foxy_time_left < 5) {
            if ((int(rm->foxy_time_left * 4)) & 1) {
                rm->sprites.attention.draw (&window);
            }
        } else if (rm->foxy_time_left < (rm->AI_level[FOXY] > 3 ? 10 : 25)) {
            if ((int(rm->foxy_time_left * 2)) & 1) {
                rm->sprites.attention.draw (&window);
            }
        }
    }
	rm->cam->sprites.info[4].draw (&window);
	if (rm->gf_blink) {
		int cc = rm->gf_count % 7;
		cc = abs(cc-3);
		rm->sprites.blink.itself.setColor (sf::Color (255,255,255,255 - cc*85));
		rm->sprites.blink.draw (&window);
	}
}