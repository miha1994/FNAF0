#pragma once
#include "main_header.h"

struct matrix_2x2 {
	float elements[2][2];
	matrix_2x2 (float e00, float e01, float e10, float e11) {
		elements[0][0] = e00;
		elements[0][1] = e01;
		elements[1][0] = e10;
		elements[1][1] = e11;
	}
	matrix_2x2 (float angle) {
		elements[0][0] = cos (angle);
		elements[0][1] = -sin (angle);
		elements[1][0] = -elements[0][1];
		elements[1][1] = elements[0][0];
	}
	v2f operator *(v2f v) {return v2f (elements[0][0] * v.x + elements[0][1] * v.y, elements[1][0] * v.x + elements[1][1] * v.y);}
};

#define forquad(q,end,vertex_array)		for(sf::Vertex *q = &(vertex_array).m_vertices[0], *end = q + (vertex_array).getVertexCount (); q < end; q += 4)
#define quad_get_pos(q)					(((q)[0].position + (q)[2].position) / float(2.0))

void quad_set_pos (sf::Vertex *q, v2f pos, v2f origin);

void quad_set_tex_rect (sf::Vertex *q, int x, int y, int w, int h);
void quad_set_tex_rect (sf::Vertex *q, v2i pos, v2i size);
void quad_set_tex_rect (sf::Vertex *q, sf::IntRect rect);

void quad_set_color (sf::Vertex *q, sf::Color color);

void quad_move (sf::Vertex *q, float offset_x, float offset_y);
void quad_move (sf::Vertex *q, v2f offset);

void quad_set_directions (sf::Vertex *q, v2f *directions, v2f *center = NULL);

void set_directions (v2f *directions, v2f rect_size, v2f *origin = NULL);

void quad_v_a (sf::Vertex *q, sf::VertexArray *v_a);

template <class T>
sf::Rect <T> operator + (sf::Rect <T> r, sf::Vector2 <T> v) {
	return sf::Rect <T> (r.left + v.x, r.top + v.y, r.width, r.height);
}

typedef sf::Vertex quad[4];