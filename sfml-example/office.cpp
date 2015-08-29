#include "office.h"
#include "o_rooms.h"
#include "rooms_extra.h"

void office_update (float dt, rooms *rm, v2f m) {
	rm->in_office_time += dt;
	rm->light_in_office = kb::isKeyPressed (kb::LControl) || kb::isKeyPressed (kb::RControl);
	if (rm->light_in_office) {
		if (rm->sounds.light_in_office.snd[0].getStatus() != sf::Sound::Playing) {
			rm->sounds.light_in_office.play ();
		}
	} else {
		if (rm->sounds.light_in_office.snd[0].getStatus() == sf::Sound::Playing) {
			rm->sounds.light_in_office.stop ();
		}
	}
	rm->x_shift += dt * speed_of_camera_movement (m.x);
	if (rm->x_shift > 320) {
		rm->x_shift = 320;
	} else if (rm->x_shift < 0) {
		rm->x_shift = 0;
	}
	if (m.x > 230 && m.x < 910 && m.y > 650) {
		if (rm->was_outside_of_switch_tab && rm->left_door_state == DOOR_STATE_OPENED && rm->right_door_state == DOOR_STATE_OPENED) {
			rm->state = ROOMS_STATE::TAB_TO_CAMERAS;
			rm->sounds.tab.play ();
			rm->tab_count = 0;
			rm->tab_sw = false;
			rm->light_in_office = false;
			rm->in_office_time = 0;
			return;
		}
	} else {
		rm->was_outside_of_switch_tab = true;
	}
	if (rm->blink_count == 2) {
		if (rm->in_office_time > 50 - 1.5f * rm->AI_level[FREDDY]) {
			rm->state = FREDDY_JUMPSCARE;
			rm->freddy_jumpscare_count = 0;
			rm->sounds.jumpscare1.play ();
			rm->sounds.jumpscare2.play ();
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
	rm->db.text.setString (std::to_string (int(m.x)) + ", " + std::to_string (int(m.y)));
}

void office_render (rooms *rm) {
	if (rm->light_in_office) {
		rm->sprites.light_office.itself.setPosition (-rm->x_shift, 0);
		rm->sprites.light_office.draw (&window);
		rm->sprites.fan[rm->fan_count].draw (&window, true, v2f(780-rm->x_shift,303));
		if ((++rm->fan_count) > 2) {
			rm->fan_count = 0;
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
	if (rm->was_outside_of_switch_tab) {
		rm->sprites.switcher_to_camera.draw (&window);
	}
}