#include "Gems.h"

void Gems::createImages() {

	if (!textures[0].loadFromFile("gem1.png")) {
		cerr << "Error loading gema1 texture" << endl;
	}
	if (!textures[1].loadFromFile("gem2.png")) {
		cerr << "Error loading banana texture" << endl;
	}
	if (!textures[2].loadFromFile("gem3.png")) {
		std::cerr << "Error loading pear texture" << std::endl;
	}
	if (!textures[3].loadFromFile("gem4.png")) {
		std::cerr << "Error loading pineapple texture" << std::endl;
	}
	if (!textures[4].loadFromFile("gem5.png")) {
		std::cerr << "Error loading orange texture" << std::endl;
	}
	for (int i = 0; i < 5; ++i) {
		fruitsImages[i].setTexture(textures[i]);

	}
}