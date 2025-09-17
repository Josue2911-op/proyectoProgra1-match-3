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
	sf::Texture& getTexture(int index) {//devuelve la textura que se usa en Board para FullMatrix y updateSprites
		return textures[index];//el index es el tipo de fruta que esta asignado por el numero random de entre las 5 
	}
	void createImages();
	~Gems() {
		delete[]textures;
		delete[]fruitsImages;
	}
};