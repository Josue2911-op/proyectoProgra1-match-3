#include "normalGem.h"
void NormalG:: match(int i, int j, int ** matrix, sf::Sprite** matrixx,Gems*** matrixG) {
	matrix[i][j]= -1;
	matrixx[i][j].setColor(sf::Color::Transparent);
}