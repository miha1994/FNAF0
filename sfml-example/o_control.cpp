#include "o_control.h"
#include "space.h"
#include "main_header.h"
#include "save.h"

char *main_control;

O_LOAD (control_load) {
	control *cnt = new control ();
	cnt->active_space = NULL;
	read_string ();
	std::string str1, str2;
	while ((str1 = read_string ()) != "}") {
		cnt->todo.push_back (get_command (str1));
	}
	read_string ();
	main_control = (char *)cnt;
	return (char *)cnt;
}

O_UPDATE (control_update) {
	CNTRL ("control_update");
	O_DECL (control, cnt);
	while (!(cnt->todo.empty ())) {
		std::string cm1 = cnt->todo.front ().first, cm2 = cnt->todo.front ().second;
		if (cm1 == "load") {
			all_spaces[cm2] = load (("assets/inf/" + cm2 + ".txt").c_str ());
		} else if (cm1 == "active") {
			cnt->active_space = all_spaces[cm2];
		} else if (cm1 == "delete") {
			all_spaces[cm2]->del ();
			all_spaces.erase (cm2);
		} else if (cm1 == "quit") {
			return true;
		} else if (cm1 == "newgame") {
		}
		cnt->todo.pop_front ();
	}
	if (cnt->active_space) {
		if ((cnt->active_space)->update (dt))
			return true;
	}
	return false;
}

O_RENDER (control_render) {
	O_DECL (control, cnt);
	if (cnt->active_space) {
		(cnt->active_space)->render ();
	}
}

O_DEL (control_del) {
	O_DECL (control, cnt);
	delete cnt;
}

std_obj_functions control_f (control_load, control_update, control_render, control_del);