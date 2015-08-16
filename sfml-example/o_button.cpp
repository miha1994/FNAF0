#include "o_button.h"
#include "o_control.h"
#include "space.h"
#include "save.h"

int night_sizes[7][2] = { {227, 97}, {231, 97}, {231, 97}, {231, 97}, {231, 97}, {233, 97}, {240, 100} };

float first_night_max_time=2.2;

O_LOAD (button_load) {
	button *btn = new button;
	btn->state = BUTTON_STATE::MENU;
	get_save_status(&btn->num_of_beaten_nigths);
	btn->active_but = 1;
	get_mouse_pos (btn->prev_m_pos);
	btn->prev_down = false;
	btn->prev_up = false;
	char str[50];
	sprites_button *spr = &btn->sprites;
	FOR (i,4) {
		sprintf (str, "assets/textures/menu/%d.png", i);
		spr->background[i].init (str, 1280, 720);
	}
	FOR (i,11) {
		sprintf (str, "assets/textures/cam_glitches/%d.png", i);
		spr->glitches[i].init (str, 1280, 720);
		spr->glitches[i].itself.setColor (sf::Color (255,255,255,80));
	}
	FOR (i,8) {
		sprintf (str, "assets/textures/cam_noize/%d.png", i);
		spr->noize[i].init (str, 1280, 720);
		spr->noize[i].itself.setColor (sf::Color (255,255,255,255));
	}
	FOR (i, 7) {
		sprintf (str, "assets/textures/inscriptions/nights/%d.png", i+1);
		sprite *s = spr->night + i;
		s->texture.loadFromFile (str);
		s->texture.setSmooth (true);
		s->itself.setTexture (s->texture);
		s->itself.setTextureRect (sf::Rect<int> (0,63,night_sizes[i][0],night_sizes[i][1] - 63));
		s->itself.setPosition (120, 487);
		s->itself.setScale (0.5, 0.5);
	}
	spr->title.init ("assets/textures/inscriptions/444.png", 201, 259);
	spr->title.itself.setPosition (120, 67);

	spr->new_game.init ("assets/textures/inscriptions/448.png", 203, 33);
	spr->new_game.itself.setPosition (120, 385);

	spr->continue_.init ("assets/textures/inscriptions/449.png", 204, 34);
	spr->continue_.itself.setPosition (120, 450);

	spr->sixth_night.init ("assets/textures/inscriptions/443.png", 227, 44);
	spr->sixth_night.itself.setPosition (120, 515);

	spr->custom_night.init ("assets/textures/inscriptions/526.png", 306, 44);
	spr->custom_night.itself.setPosition (120, 580);

	spr->pointer.init ("assets/textures/inscriptions/450.png", 43, 26);

	spr->first_night.init ("assets/textures/other/539.png", 1280, 720);
	spr->black_screen.init ("assets/textures/other/539.png", 1280, 720);
	spr->black_screen.itself.setColor (sf::Color (0,0,0, 255));

	spr->loading.init ("assets/textures/other/482.png", 40, 40);
	spr->loading.itself.setPosition (1215, 655);

	btn->theme.loadFromFile ("assets/snd/darkness music.wav", 100);
	btn->theme.snd[0].setLoop (1);
	btn->static_.loadFromFile ("assets/snd/static2.wav", 100);
	btn->item.loadFromFile ("assets/snd/blip3.wav", 100);

	btn->bg_counter1 = 0;
	btn->noize_counter = 0;
	btn->noize_r = 0;
	btn->darkness_counter = 0;
	btn->darkness_r = 0;
	btn->darkness2_counter = 0;
	btn->darkness2_r = 0;
	btn->glitches_counter = 0;
	btn-> glitches_r = 0;
	btn->static_glitch_shift = 0;

	btn->buttons[0].is_active = true;
	btn->buttons[0].is_current = false;
	btn->buttons[0].next = btn->buttons + 1;
	btn->buttons[0].prev = NULL;
	btn->buttons[0].spr = &btn->sprites.new_game;

	btn->buttons[1].is_active = true;
	btn->buttons[1].is_current = true;
	btn->buttons[1].next = btn->buttons + 2;
	btn->buttons[1].prev = btn->buttons + 0;
	btn->buttons[1].spr = &btn->sprites.continue_;

	btn->buttons[2].is_active = btn->num_of_beaten_nigths > 4;
	btn->buttons[2].is_current = false;
	btn->buttons[2].next = btn->buttons + 3;
	btn->buttons[2].prev = btn->buttons + 1;
	btn->buttons[2].spr = &btn->sprites.sixth_night;

	btn->buttons[3].is_active = btn->num_of_beaten_nigths > 5;
	btn->buttons[3].is_current = false;
	btn->buttons[3].next = NULL;
	btn->buttons[3].prev = btn->buttons + 2;
	btn->buttons[3].spr = &btn->sprites.custom_night;

	btn->first_night_time1 = 0;
	btn->first_night_time2 = -1;
	btn->show_the_number_of_nigth_time = 0;

	btn->exit = false;
	read_string ();
	return (char *)btn;
}

O_UPDATE (button_update) {
	CNTRL ("button_update");
	O_DECL (button, btn);
	v2f m;
	bool same_pos = m == btn->prev_m_pos;
	int m_but = -1;
	bool go = false;
	switch (btn->state) {
	case BUTTON_STATE::MENU:
		get_mouse_pos (m);
		if (btn->theme.snd[0].getStatus () != sf::Sound::Playing) {
			btn->theme.play ();
			btn->static_.play ();
		}
		btn->prev_m_pos = m;

		
		FOR (i, 4) {
			if (!btn->buttons[i].is_active) {
				break;
			}
			if (btn->buttons[i].spr->itself.getGlobalBounds().contains (v2f(m))) {
				m_but = i;
				break;
			}
		}
		if (m_but >= 0 && !same_pos && m_but != btn->active_but) {
			btn->buttons[btn->active_but].is_current = false;
			btn->active_but = m_but;
			btn->buttons[btn->active_but].is_current = true;
			btn->item.play ();
		}

		if (kb::isKeyPressed (kb::Down)) {
			if (!btn->prev_down) {
				if (btn->buttons[btn->active_but].next && btn->buttons[btn->active_but].next->is_active) {
					btn->buttons[btn->active_but].is_current = false;
					btn->active_but++;
					btn->buttons[btn->active_but].is_current = true;
					btn->item.play ();
				}
				btn->prev_down = true;
			}
		} else {
			btn->prev_down = false;
		}
		if (kb::isKeyPressed (kb::Up)) {
			if (!btn->prev_up) {
				if (btn->buttons[btn->active_but].prev) {
					btn->buttons[btn->active_but].is_current = false;
					btn->active_but--;
					btn->buttons[btn->active_but].is_current = true;
					btn->item.play ();
				}
				btn->prev_up = true;
			}
		} else {
			btn->prev_up = false;
		}
		if (sf::Mouse::isButtonPressed (sf::Mouse::Left)) {
			FOR (i, 4) {
				if (btn->buttons[i].is_active && btn->buttons[i].spr->itself.getGlobalBounds ().contains (m)) {
					btn->active_but = i;
					go = true;
				}
			}
		}
		if (kb::isKeyPressed (kb::Return)) {
			go = true;
		}
		if (go) {
			switch (btn->active_but) {
			case 1:
				if (btn->num_of_beaten_nigths) {
					btn->state = BUTTON_STATE::SHOW_THE_NUMBER_OF_NIGHT;
					btn->item.play ();
					btn->static_.stop ();
					btn->theme.stop ();
					btn->glitches_counter = 0;
				}
				btn->choosed_night = Min (btn->num_of_beaten_nigths + 1, 5);
			case 0:
				btn->state = BUTTON_STATE::FIRST_NIGHT;
				btn->item.play ();
				btn->choosed_night = 1;
			}
		}
	
		btn->sprites.pointer.itself.setPosition (40, btn->buttons[btn->active_but].spr->itself.getPosition().y + 6);
		if ((btn->static_glitch_shift += dt*50) > 800) {
			btn->static_glitch_shift = 0;
		}
		break;
	case BUTTON_STATE::FIRST_NIGHT:
		if (btn->first_night_time1 < first_night_max_time) {
			btn->first_night_time1 += dt;
		} else {
			if (btn->first_night_time2 < 0) {
				if (Global_Bool_Key_Pressed || sf::Mouse::isButtonPressed (sf::Mouse::Left)|| sf::Mouse::isButtonPressed (sf::Mouse::Right)) {
					btn->first_night_time2 = 0;
				}
			} else {
				if (btn->first_night_time2 < first_night_max_time) {
					btn->first_night_time2 += dt;
				} else {
					btn->state = SHOW_THE_NUMBER_OF_NIGHT;
					btn->item.play ();
					btn->static_.stop ();
					btn->theme.stop ();
					btn->glitches_counter = 0;
				}
			}

		}
		break;
	case BUTTON_STATE::SHOW_THE_NUMBER_OF_NIGHT:
		btn->show_the_number_of_nigth_time += dt;
		if (btn->exit) {
			control *mc = (control *)main_control;
			mc->todo.push_back (instruction ("delete", "MENU"));
			mc->todo.push_back (instruction ("load", "L0"));
			mc->todo.push_back (instruction ("active", "L0"));
		}
		break;
	}
	return false;
}

void draw_main_menu (button *btn) {
	if (btn->darkness_counter--) {
	} else {
		btn->darkness_counter = 7;
		btn->darkness_r = rand() % 256;
		FOR (i, 4) {
			btn->sprites.background[i].itself.setColor (sf::Color (255,255,255,btn->darkness_r));
		}
	}

	if (btn->bg_counter1) {
		if (btn->bg_counter2--) {
			btn->sprites.background[btn->bg_r].draw (&window);
		} else {
			if (--btn->bg_counter1) {
				btn->bg_counter2 = 3;
				btn->bg_r = 1 + (rand () %3);
			}
		}
	} else  {
		btn->sprites.background[0].draw (&window);
		if (rand () > 32600) {
			btn->bg_counter1 = 3;
			btn->bg_counter2 = 3;
			btn->bg_r = 1 + (rand () %3);
		}
	}
	btn->sprites.title.draw (&window);
	FOR (i, 4) {
		if (btn->buttons[i].is_active) {
			btn->buttons[i].spr->draw (&window);
		}
	}
	if (btn->buttons[1].is_current) {
		btn->sprites.night[btn->num_of_beaten_nigths].draw (&window);
	}
	btn->sprites.pointer.draw (&window);

	if (btn->noize_counter--) {
	} else {
		btn->noize_counter = 0;
		btn->noize_r = (btn->noize_r + 1) % 8;
	}
	if (btn->darkness2_counter--) {
	} else {
		btn->darkness2_counter = 7;
		btn->darkness2_r = 100 + rand() % 156;
	}
	btn->sprites.noize[btn->noize_r].itself.setColor (sf::Color (255,255,255,btn->darkness2_r));
	btn->sprites.noize[btn->noize_r].draw(&window);

	if (btn->glitches_counter) {
		btn->sprites.glitches[btn->glitches_r].itself.setPosition (0, 0);
		btn->sprites.glitches[btn->glitches_r].draw (&window);
		btn->glitches_counter--;
		if (rand () > 28000) {
			btn->glitches_counter = 5;
			btn->glitches_r = rand () % 11;
		}
	} else if (rand () > 28000) {
		btn->glitches_counter = 5;
		btn->glitches_r = rand () % 11;
	}
	btn->sprites.glitches[5].itself.setPosition (0, btn->static_glitch_shift - 500);
	btn->sprites.glitches[5].draw (&window);
}

O_RENDER (button_render) {
	O_DECL (button, btn);

	switch (btn->state) {
	case MENU:
		draw_main_menu (btn);
		break;
	case FIRST_NIGHT:
		if (btn->first_night_time1 < first_night_max_time) {
			draw_main_menu (btn);
		}
		btn->sprites.first_night.itself.setColor (sf::Color (255,255,255,255.0 * std::min (1.0f, (btn->first_night_time1/first_night_max_time))));
		btn->sprites.first_night.draw (&window);
		if (btn->first_night_time2 >= 0) {
			btn->sprites.black_screen.itself.setColor (sf::Color (0,0,0,255.0 * std::min (1.0f, (btn->first_night_time2/first_night_max_time))));
			btn->sprites.black_screen.draw (&window);
		}
		break;
	case SHOW_THE_NUMBER_OF_NIGHT:
		if (btn->show_the_number_of_nigth_time < first_night_max_time) {
			sprite *spr = btn->sprites.night + btn->choosed_night - 1;
			spr->itself.setTextureRect (sf::Rect <int> (0,0,night_sizes[btn->choosed_night - 1][0], night_sizes[btn->choosed_night - 1][1]));
			spr->itself.setScale (1,1);
			spr->itself.setOrigin (night_sizes[btn->choosed_night - 1][0]/2.0, night_sizes[btn->choosed_night - 1][1]/2.0);
			spr->itself.setPosition (640, 360);
			spr->itself.setColor (sf::Color::White);
			spr->draw (&window);
			if (btn->glitches_counter < 6) {
				btn->sprites.glitches[10-btn->glitches_counter].itself.setColor (sf::Color::White);
				btn->sprites.glitches[10-btn->glitches_counter].draw (&window);
				btn->glitches_counter++;
			}
		} else {
			btn->exit = true;
			btn->sprites.black_screen.itself.setColor (sf::Color::Black);
			btn->sprites.black_screen.draw (&window);
			btn->sprites.loading.draw (&window);
		}
	}
}

O_DEL (button_del) {
	O_DECL (button, btn);
	delete btn;
}

std_obj_functions button_f (button_load, button_update, button_render, button_del);