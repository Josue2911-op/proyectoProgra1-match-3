#include "PowerGem.h"
#include "Board.h"
void PowerGem::match(int i, int j, int** matrix, sf::Sprite** matrixx,Gems***matrixG ) {
	try {
		Board::deletePower++;
		for (int u = 0; u < 8; u++) {
			if (u != j && matrixG[i][u] != nullptr && !matrixG[i][u]->fading) {
				int type = matrixG[i][u]->getType();
				if (type == 5) Board::deleteIce++;
				else if (type == 6) Board::deletePower++;
				matrixG[i][u]->fadeOut();//activa el fade
				matrix[i][u] = -2;//marca posicion vacia para gravity
			}
		}
		for (int k = 0; k < 8; k++) {
			if (k != i && matrixG[k][j] != nullptr && !matrixG[k][j]->fading) {
				int type = matrixG[k][j]->getType();
				if (type == 5) Board::deleteIce++;
				else if (type == 6) Board::deletePower++;
				matrixG[k][j]->fadeOut();
				matrix[k][j] = -2;
			}

		}
		if (matrixG[i][j] != nullptr && !matrixG[i][j]->fading) {
			matrixG[i][j]->fadeOut();
			matrix[i][j] = -2;
		}
	}
	catch (const exception& e) {
		cerr << "Error en PowerGem match: " << e.what() << endl;
		exit(1);
	}
}