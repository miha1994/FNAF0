#include "space.h"
#include "func_pointers.h"
#include "save.h"

std::map<std::string, space*> all_spaces;

space *load (const char *file_name) {
	CNTRL ("space_load");
	space *new_space = new space;
	new_space->need_reset = false;
	freopen (file_name, "r", stdin);
	int number_of_textures = read_int ();
	if (number_of_textures) {
		new_space->textures = new sf::Texture [number_of_textures];
		FOR (i, number_of_textures) {
			std::string s = read_string ();
			new_space->textures[i].loadFromFile (s);
			
			new_space->textures[i].setSmooth (read_int ());
		}
	}
	else {
		new_space->textures = NULL;
	}

	read_string ();	// read "{"
	std::string type_id;
	int num;
	while ((type_id = read_string ()) != "}") {
		int num = min_type_info[type_id].num;
		new_space->all_types[num].functions = fp_array[min_type_info[type_id.c_str ()].index_in_fp_array];
		read_string (); // skip "{"
		new_space->all_types[num].objects.push_back (new_space->all_types[num].functions->load ((char*)new_space));
	}
	fclose (stdin);
	return new_space;
}

bool space::update (float dt) {
	CNTRL ("space_update");
	if (need_reset) {
		int new_part = part;
		bool same_part = prev_part == part;
		if (!same_part) {
			part = prev_part;
			forvector (p, end, v2i, p_types) {
				if (all_types[p->x].functions->store) {
					all_types[p->x].functions->store (all_types[p->x].objects.back(), all_types[p->y].objects[prev_part]);
				}
			}
			prev_part = new_part;
		}
		part = new_part;
		std_obj_functions *func;
		forvector (p, end, v2i, p_types) {
			func = all_types[p->x].functions;
			if (func->reset && (!same_part || func->reset_same_part)) {
				func->reset (all_types[p->x].objects.back(), all_types[p->y].objects[part],(char *) this);
			}
		}
		need_reset = false;
	}
	int i = 0;
	formap (p, end, int, type, all_types) {
		if (p->second.functions->update) {
			if (p->second.functions->update (p->second.objects.back (), dt)) {
				return true;
			}
		}
		++i;
	}
	return false;
}

void space::render () {
	bool repeat = false;
	std::list <int> repeat_list;
	formap (p, end, int, type, all_types) {
		if (p->second.functions->render) {
			p->second.functions->render (p->second.objects.back(), &repeat);
			if (repeat) {
				repeat = false;
				repeat_list.push_back (p->first);
			}
		}
	}
	if (!repeat_list.empty ()) {
		repeat = true;
		forlist (p, end, int, repeat_list) {
			all_types[*p].functions->render (all_types[*p].objects.back (), &repeat);
		}
	}
}

void space::del () {
	forvector (p, end, v2i, p_types) {
		if (all_types[p->x].functions->store) {
			all_types[p->x].functions->store (all_types[p->x].objects.back(), all_types[p->y].objects[part]);
		}
	}
	formap (p, end, int, type, all_types) {
		forvector (p1, end1, char*, p->second.objects) {
			p->second.functions->del (*p1);
		}
	}
	all_types.clear ();
}