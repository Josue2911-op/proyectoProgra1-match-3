#include "IceGem.h"
void IceGem::match(int i, int j, int** matrix, sf::Sprite** matrixx,Gems***matrixG) {
	if (hits > 0) {
		hits--;
	}
	if (hits == 1) {
			sprite.setTexture(Gems::textures[7]);
			sprite.setScale(0.1f, 0.1f);
			matrixx[i][j] = sprite;
	}else{
		matrix[i][j] = -1;
		if (matrixG[i][j] != nullptr) {
			delete matrixG[i][j];
			matrixG[i][j] = nullptr;
		}
		matrixx[i][j].setColor(sf::Color::Transparent);
	}
}