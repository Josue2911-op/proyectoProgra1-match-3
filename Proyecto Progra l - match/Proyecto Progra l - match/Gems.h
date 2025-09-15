#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Gems {
private:
	sf::Texture* textures;
	sf::Sprite* fruitsImages;
	
public:
	Gems() {
		textures = new sf::Texture[5];
		
		fruitsImages = new sf::Sprite [5];
	}
	sf::Sprite getfruitsImages(int index) {
			return fruitsImages[index];
		
	}
	void createImages();
};