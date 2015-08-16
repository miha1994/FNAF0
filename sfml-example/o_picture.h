#pragma once
#include <vector>
#include "object.h"
#include "sfml.h"

class picture {
public:
	sf::VertexArray v_a;
	sf::RenderStates r_s;
	sf::Music mus;
};

extern std_obj_functions picture_f;