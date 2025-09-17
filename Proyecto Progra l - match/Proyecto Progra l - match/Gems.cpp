#include "Gems.h"

void Gems::createImages() {

	if (!textures[0].loadFromFile("gem1.png")) {//carga las texturas y las asigna a un arreglo en n posicion
		cerr << "Error loading gema1 texture" << endl;
	}
	if (!textures[1].loadFromFile("gem2.png")) {
		cerr << "Error loading banana texture" << endl;
	}
	if (!textures[2].loadFromFile("gem3.png")) {
		cerr << "Error loading pear texture" << endl;
	}
	if (!textures[3].loadFromFile("gem4.png")) {
		cerr << "Error loading pineapple texture" << endl;
	}
	if (!textures[4].loadFromFile("gem5.png")) {
		cerr << "Error loading orange texture" << endl;
	}
	for (int i = 0; i < 5; ++i) {
		fruitsImages[i].setTexture(textures[i]);//asigna textura a sprite

	}
}