#include "some_structures.h"
#include "main_header.h"

void sprite::init(char *file_name, int size_x, int size_y) {
	texture.loadFromFile (file_name);
	texture.setSmooth (true);
	itself.setTexture (texture);
	itself.setTextureRect (sf::Rect<int> (0,0,size_x,size_y));
}

void sprite::draw (sf::RenderWindow *wnd, bool f, v2f xy) {
	if (f) {
		itself.setPosition (xy);
	}

	v2f o2 = itself.getPosition ();
	v2f n2 = o2;
	n2.x *= X_FACTOR;
	n2.y *= Y_FACTOR;
	itself.setPosition (n2);

	v2f o3 = itself.getScale ();
	v2f n3 = o3;
	n3.x *= X_FACTOR;
	n3.y *= Y_FACTOR;
	itself.setScale (n3);

	wnd->draw (itself);

	itself.setPosition (o2);
	itself.setScale (o3);
}