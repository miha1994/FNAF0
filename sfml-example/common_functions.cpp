#include "object.h"
#include "space.h"
#include "main_header.h"

int MY_WIND_WIDTH = 1280, MY_WIND_HEIGHT = 720;
int R_WIND_WIDTH, R_WIND_HEIGHT;
float X_FACTOR, Y_FACTOR;
bool Global_Bool_Key_Pressed;
std::map <std::string, my_type_info> min_type_info;

sf::RenderWindow window;

int part = 0;
int level = -1;
int num_of_levels = 4;
int num_of_parts = 0;
bool mouse_left_pressed;

O_LOAD (no_load) {
	read_char ();
	return NULL;
}

instruction get_command(std::string cm1) {
	if (cm1 == "load" || cm1 == "active" || cm1 == "delete") {
		std::string cm2 = read_string ();
		return std::make_pair (cm1, cm2);
	}
	else if (cm1 == "quit" || cm1 == "newgame") {
		return std::make_pair (cm1, "");
	}
}

v2i std_directions[] = {
	v2i (0,-1),
	v2i (1,0),
	v2i (0,1),
	v2i (-1,0)
};

int vec_to_dir (v2i v) {
	if (v.x) {
		return v.x > 0 ? 1 : 3;
	}
	else {
		return v.y > 0 ? 2 : 0;
	}
}

float length (v2f v) {
	return sqrt (v.x * v.x + v.y * v.y);
}

struct my_rect_ {
	v2f v0;
	v2f v1;
	my_rect_ () {}
	my_rect_ (sf::FloatRect r) : v0 (r.left, r.top), v1 (r.left + r.width, r.top + r.height) {}
	my_rect_ (float x0, float y0, float x1, float y1) : v0 (x0, y0), v1 (x1, y1) {}
};

float min4 (float a, float b, float c, float d) {
	a = Min (a, b);
	c = Min (c, d);
	return Min (a,c);
}

float max4 (float a, float b, float c, float d) {
	a = Max (a, b);
	c = Max (c, d);
	return Max (a,c);
}

float vec_to_pi (v2f vector_) {
	if (length(vector_)) {
		v2f v (-vector_.y, vector_.x);
		v = v / length (v);
		float angle = acos (v.x);
		if (v.y < 0) {
			angle = 6.28 - angle;
		}
		return angle;
	}
	return -100;
}

struct {
	std::string f_type;
	bool print;
} in_out_d_info[] = {
	"load", 0,
	"del", 0,
	"reset", 0,
	"update", 0,
	"space_load", 0,
	"space_update", 0,
	"control_update", 0,
	"run", 0
};

#define TEST print && kb::isKeyPressed (kb::P)

in_out_d::in_out_d (std::string s) {
	func_name = s;
	print = false;
	for (auto x : in_out_d_info) {
		if (func_name.find(x.f_type) != std::string::npos && x.print) {
			print = true;
			break;
		}
	}
	if (TEST) {
		printf ("%s in\n", func_name.c_str ());
	}
}

in_out_d::~in_out_d () {
	if (TEST) {
		printf ("%s out\n", func_name.c_str ());
	}
}

void del_list_push (std::list <int> *list, int new_element) {
	forlist (p, end, int, *list) {
		if (new_element > *p) {
			list->insert (p, new_element);
			return ;
		} else if (new_element == *p) {
			return ;
		}
	}
	list->push_back (new_element);
}