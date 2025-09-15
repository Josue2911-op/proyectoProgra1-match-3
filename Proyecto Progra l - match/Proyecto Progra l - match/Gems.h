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
	sf::Texture& getTexture(int index) {
		return textures[index];
	}
	void createImages();
};