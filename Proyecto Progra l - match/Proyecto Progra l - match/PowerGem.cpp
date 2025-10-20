#include "PowerGem.h"
void PowerGem::match(int i, int j, int** matrix, sf::Sprite** matrixx,Gems***matrixG) {
	for (int u = 0; u < 8; u++) {
		if (u != j&& matrixG[i][u]!=nullptr && !matrixG[i][u]->fading) {
			matrixG[i][u]->fadeOut();
			matrix[i][u] = -2;
		}
	}
	for (int k = 0; k < 8; k++) {
		if (k != i && matrixG[k][j]!=nullptr && !matrixG[k][j]->fading) {
			matrixG[k][j]->fadeOut();
			matrix[k][j] = -2;
		}
		
	}
	if (matrixG[i][j] != nullptr && !matrixG[i][j]->fading) {
		matrixG[i][j]->fadeOut();
		matrix[i][j] = -2;
	}
}