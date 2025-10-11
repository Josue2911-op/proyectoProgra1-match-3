#pragma once
#include "Gems.h"
class NormalG :public Gems {
private:
	int type;
	sf::Sprite sprite3;
public:
	NormalG(int tp) {
		type = tp;
		sprite3.setTexture(Gems::textures[type]);
		sprite3.setScale(0.1f, 0.1f);
	}
	void match(int i, int j, int ** matrix, sf::Sprite** matrixx,Gems*** matrixG)override;
	int getType()override {
		return type;
	}
	sf::Sprite& getSprite() override{
		return sprite3;
	}
};