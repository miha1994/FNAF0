#pragma once
#include "sfml.h"
#include "main_header.h"

struct sprite {
	sf::Texture texture;
	sf::Sprite itself;
	void init(char *file_name, int size_x, int size_y);
	void draw (sf::RenderWindow *wnd, bool coords = false, v2f xy = v2f(0,0));
};

#define get_mouse_pos(v2if)		{v2i i2 = sf::Mouse::getPosition (window); v2if.x = i2.x / X_FACTOR; v2if.y = i2.y / Y_FACTOR;}