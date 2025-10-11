#include "Gems.h"
sf::Texture Gems::textures[8];
void Gems::createImages() {

	if (!textures[0].loadFromFile("gem1.png")) {//carga las texturas y las asigna a un arreglo en n posicion
		cerr << "Error loading gem1 texture" << endl;
	}
	if (!textures[1].loadFromFile("gem2.png")) {
		cerr << "Error loading gem2 texture" << endl;
	}
	if (!textures[2].loadFromFile("gem3.png")) {
		cerr << "Error loading gem3 texture" << endl;
	}
	if (!textures[3].loadFromFile("gem4.png")) {
		cerr << "Error loading gem4 texture" << endl;
	}
	if (!textures[4].loadFromFile("gem5.png")) {
		cerr << "Error loading gem5 texture" << endl;
	}if (!textures[5].loadFromFile("iceGem.png")) {
		cerr << "Error loading iceGem texture" << endl;
	}
	if (!textures[6].loadFromFile("powerGem.png")) {
		cerr << "Error loading powerGem texture" << endl;
	}
	if (!textures[7].loadFromFile("breakIce.png")) {
		cerr << "Error loading breakIce texture" << endl;
	}
}