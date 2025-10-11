#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Gems {
protected:
	static sf::Texture textures[8];

public:
	Gems() {
	}
	sf::Texture& getTexture(int index) {//devuelve la textura que se usa en Board para FullMatrix y updateSprites
		return textures[index];//el index es el tipo de fruta que esta asignado por el numero random de entre las 5 
	}
	virtual int getType() = 0;
	virtual sf::Sprite& getSprite() = 0;
	virtual void match(int i,int j,int** matrix,sf::Sprite** matrixx, Gems***matrixG)=0;
	static void createImages();
	~Gems() {
		
		
	}
};