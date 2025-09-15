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
	sf::Sprite& getFruitsImages(int index) {
		sf::Sprite tr;
		tr.setTexture(textures[index]);
		tr.setColor(sf::Color::White);
		tr.setScale(0.1f, 0.1f);
		return tr;
		
	}
	void createImages();
};