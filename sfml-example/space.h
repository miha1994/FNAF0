#pragma once

#include "main_header.h"
#include <map>
#include <string>
#include <vector>
#include "object.h"

class type {
public:
	vec<char *> objects;
	std_obj_functions *functions;
};

class space {
public:
	std::map <int, type> all_types;
	sf::Texture *textures;
	bool need_reset;
	int prev_part;
	vec<v2i> p_types; // x - type, y - type_p
	friend space * load (const char *filename);
	bool update (float dt); // возвращает 1, если необходимо завершить выполнение программы
	void render ();
	void del ();
};

extern std::map<std::string, space*> all_spaces;