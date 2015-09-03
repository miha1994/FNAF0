#include "Game.h"
#include "func_pointers.h"
#include "main_header.h"
#include "space.h"

bool Game::init (bool fullscreen) {
	std::vector <sf::VideoMode> f_modes = sf::VideoMode::getFullscreenModes ();
	R_WIND_WIDTH = f_modes[0].width;
	R_WIND_HEIGHT = f_modes[0].height;
	X_FACTOR = float (R_WIND_WIDTH) / float (MY_WIND_WIDTH);
	Y_FACTOR = float (R_WIND_HEIGHT) / float (MY_WIND_HEIGHT);
	window.create (f_modes[0], "Five Nights at Freddy's 0", fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	window.setVerticalSyncEnabled (true);
	window.setFramerateLimit (60);
	min_type_info["CONTROL"]	= my_type_info (0, 0);
	min_type_info["B_PICTURE"]	= my_type_info (1, 1);
	min_type_info["BUTTON"]		= my_type_info (2, 2);
	min_type_info["ROOMS"]		= my_type_info (3, 3);

	all_spaces["MAIN"] = load ("assets/inf/main.txt");
	running = true;
	mouse_left_pressed = 0;
	return true;
}
bool mplm[10] = {0};
void Game::update () {
	CNTRL ("game_update");
	rand ();
	if (!window.isOpen ()) {
		running = false;
		return;
	}
    sf::Event event;
	Global_Bool_Key_Pressed = false;
    while (window.pollEvent(event))
    {
		switch (event.type) {
        case sf::Event::Closed:
            window.close();
			running = false;
			break;
		case sf::Event::KeyPressed:
			Global_Bool_Key_Pressed = true;
		default:
			break;
		}
	}

	mouse_left_pressed = sf::Mouse::isButtonPressed (sf::Mouse::Left);

	float dt = (clock.restart ()).asSeconds ();
	if (dt > 1) {
		dt = 0;
	}
	if (all_spaces["MAIN"]->update (dt)) {
		running = false;
	}
	if (kb::isKeyPressed (kb::Escape)) {
		running = false;
	}
}

#include "quad.h"

void Game::render () {
	CNTRL ("game_render");
	window.clear ();
	if (v2u (R_WIND_WIDTH, R_WIND_HEIGHT) != window.getSize ()) {
		R_WIND_WIDTH = window.getSize ().x;
		R_WIND_HEIGHT = window.getSize ().y;
	}
	all_spaces["MAIN"]->render ();

	window.display ();
}

void Game::del () {
	CNTRL ("game_del");
	formap(p,end,std::string,space*,all_spaces) {
		p->second->del ();
		delete p->second;
	}
	window.close ();
}