#pragma once
#include "Gems.h"
class PowerGem :public Gems{
private:

	sf::Sprite sprite2;
public:
	PowerGem() {
		sprite2.setTexture(Gems::textures[6]);
		sprite2.setScale(0.1f, 0.1f);
	}
	void match(int i, int j, int**matrix, sf::Sprite** matrixx,Gems***matrixG)override;
	sf::Sprite& getSprite()override {
		return sprite2;
	}
	int getType()override {
		return 6;
	}
};