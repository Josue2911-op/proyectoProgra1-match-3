#pragma once
#include "Gems.h"
class NormalG :public Gems {
private:
	int type;
	
public:
	NormalG(int tp) {
		type = tp;
		sprite.setTexture(Gems::textures[type]);
		sprite.setScale(0.1f, 0.1f);
	}
	void match(int i, int j, int ** matrix, sf::Sprite** matrixx,Gems*** matrixG)override;
	int getType()override {
		return type;
	}
	sf::Sprite& getSprite() override{
		return sprite;
	}
};