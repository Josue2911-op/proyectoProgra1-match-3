#include "Gems.h"
sf::Texture Gems::textures[8];
void Gems::createImages() {
	try {
		if (!textures[0].loadFromFile("gem1.png")) {//carga las texturas y las asigna a un arreglo en n posicion
			throw runtime_error("Error loading gem1 texture");
		}
		if (!textures[1].loadFromFile("gem2.png")) {
			throw runtime_error("Error loading gem2 texture");
		}
		if (!textures[2].loadFromFile("gem3.png")) {
			throw runtime_error("Error loading gem3 texture");
		}
		if (!textures[3].loadFromFile("gem4.png")) {
			throw runtime_error("Error loading gem4 texture");
		}
		if (!textures[4].loadFromFile("gem5.png")) {
			throw runtime_error("Error loading gem5 texture");
		}if (!textures[5].loadFromFile("iceGem.png")) {
			throw runtime_error("Error loading iceGem texture");
		}
		if (!textures[6].loadFromFile("powerGem.png")) {
			throw runtime_error("Error loading powerGem texture");
		}
		if (!textures[7].loadFromFile("breakIce.png")) {
			throw runtime_error("Error loading breakIce texture");
		}
	}
	catch (const exception& e) {
		cerr << "Error en createImages: " << e.what() << endl;
		exit(1);
	}
}