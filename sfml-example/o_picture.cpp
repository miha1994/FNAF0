#include "o_picture.h"
#include "space.h"
#include "quad.h"

O_LOAD (picture_load) {
	CNTRL ("picture_load");
	space *par_space = (space *)parent_space;
	picture *pct = new picture ();
	quad tmp;
	int left, top, w, h;
	pct->v_a.setPrimitiveType (sf::Quads);
	while (read_string () == "{") {
		pct->r_s.texture = &(par_space->textures[read_int ()]);
		w = read_int ();
		h = read_int ();
		if (w < 0) {
			w = -w;
			pct->mus.openFromFile ("assets/snd/main_menu.wav");
			pct->mus.setLoop (true);
			pct->mus.play ();
		}
		left = read_int ();
		top = read_int ();
		quad_set_tex_rect (tmp, sf::IntRect (left, top, w, h));
		left = read_int ();
		top = read_int ();
		left *= X_FACTOR;
		w *= X_FACTOR;
		top *= Y_FACTOR;
		h *= Y_FACTOR;
		v2f directions[4];
		set_directions (directions, v2f (w,h));
		v2f center (left + w/2, top + h/2);
		quad_set_directions (tmp, directions, &center);
		quad_v_a (tmp, &pct->v_a);
		read_string ();
	}
	return (char *)pct;
}

O_RENDER (picture_render) {
	CNTRL ("picture_render");
	O_DECL (picture, pct);
	window.draw (pct->v_a, pct->r_s);
}

O_DEL (picture_del) {
	CNTRL ("picture_del");
	O_DECL (picture, pct);
	delete pct;
}

std_obj_functions picture_f (picture_load, NULL, picture_render, picture_del, NULL);