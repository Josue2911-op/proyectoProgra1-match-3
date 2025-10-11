#include "PowerGem.h"
void PowerGem::match(int i, int j, int** matrix, sf::Sprite** matrixx,Gems***matrixG) {
	for (int u = 0; u < 8; u++) {
		if (u != j&& matrixG[i][u]!=nullptr) {
			delete matrixG[i][u];
			matrixG[i][u] = nullptr;
			matrix[i][u] = -1;
			matrixx[i][u].setColor(sf::Color::Transparent);
		}
	}
	for (int k = 0; k < 8; k++) {
		if (k != i && matrixG[k][j]!=nullptr) {
			delete matrixG[k][j];
			matrixG[k][j] = nullptr;
			matrix[k][j] = -1;
			matrixx[k][j].setColor(sf::Color::Transparent);
		}
		
	}
	if (matrixG[i][j] != nullptr) {
		delete matrixG[i][j];
		matrixG[i][j] = nullptr;
		matrix[i][j] = -1;
		matrixx[i][j].setColor(sf::Color::Transparent);
	}
}