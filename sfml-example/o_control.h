#pragma once
#include "object.h"
#include "space.h"
#include <list>

class control {
public:
	space *active_space;
	to_do_list todo;
};

extern std_obj_functions control_f;