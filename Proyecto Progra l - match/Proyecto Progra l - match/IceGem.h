#pragma once
#include"Gems.h"
class IceGem:public Gems{
private:
	int hits;
	sf::Sprite sprite;
public:
	IceGem() {
		hits = 2;
		sprite.setTexture(Gems::textures[5]);
		sprite.setScale(0.1f, 0.1f);
	}
	void match(int i,int j, int** matrix,sf::Sprite** matrixx,Gems***matrixG)override;
	sf::Sprite& getSprite()override {
		return sprite;
	}
	int getType()override {
		return 5;
	}

};
