#include "quad.h"

void quad_set_pos (sf::Vertex *q, v2f pos, v2f origin) {
	FOR (i, 4) {
		q[i].position = pos - origin + q[i].texCoords - q[0].texCoords;
	}
}

void quad_set_tex_rect (sf::Vertex *q, int x, int y, int w, int h) {
	q[0].texCoords.x = x;
	q[0].texCoords.y = y;
	q[1].texCoords.x = x+w;
	q[1].texCoords.y = y;
	q[2].texCoords.x = x+w;
	q[2].texCoords.y = y+h;
	q[3].texCoords.x = x;
	q[3].texCoords.y = y+h;
}

void quad_set_tex_rect (sf::Vertex *q, v2i pos, v2i size) {
	quad_set_tex_rect(q, (pos).x, (pos).y, (size).x, (size).y);
}

void quad_set_tex_rect (sf::Vertex *q, sf::IntRect rect) {
	quad_set_tex_rect (q, rect.left, rect.top, rect.width, rect.height);
}

void quad_set_color (sf::Vertex *q, sf::Color color) {
	FOR (i, 4) {
		q[i].color = color;
	}
}

void quad_move (sf::Vertex *q, float offset_x, float offset_y) {
	FOR (i, 4) {
		q[i].position.x += offset_x;
		q[i].position.y += offset_y;
	}
}

void quad_move (sf::Vertex *q, v2f offset) {
	FOR (i, 4) {
		q[i].position += offset;
	}
}

void quad_set_directions (sf::Vertex *q, v2f *directions, v2f *center) {
	v2f center_;
	if (!center) {
		center_ = (q[0].position + q[2].position) * float(0.5);
	} else {
		center_ = *center;
	}
	FOR (i, 4) {
		q[i].position = center_ + directions[i];
	}
}

void set_directions (v2f *directions, v2f rect_size, v2f *origin) {
	directions[0].x = 0;
	directions[0].y = 0;
	directions[1].x = rect_size.x;
	directions[1].y = 0;
	directions[2].x = rect_size.x;
	directions[2].y = rect_size.y;
	directions[3].x = 0;
	directions[3].y = rect_size.y;
	v2f r_o;
	if (origin) {
		r_o = *origin;
	} else {
		r_o.x = rect_size.x / 2;
		r_o.y = rect_size.y / 2;
	}
	FOR (i, 4) {
		directions[i] -= r_o;
	}
}

void quad_v_a (sf::Vertex *q, sf::VertexArray *v_a) {
	FOR (i, 4) {
		v_a->append (q[i]);
	}
}