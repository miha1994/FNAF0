#pragma once

#include "sfml.h"
#include <map>
#include "main_header.h"

class Game {
public:
	sf::Clock clock;
	bool running;
	int mouse_count;

	Game () : running (false) {}

	bool init (bool fullscreen);

	void update ();
	void render ();

	void del ();
};