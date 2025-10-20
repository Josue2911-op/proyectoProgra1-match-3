#include "normalGem.h"

void NormalG::match(int i, int j, int** matrix, sf::Sprite** matrixx, Gems*** matrixG) {
    try {
        if (matrixG[i][j] && !matrixG[i][j]->fading) {
            matrixG[i][j]->fadeOut(); // activa el fade
            matrix[i][j] = -2;        // marca la posición vacía para gravity
        }
    }
    catch (const exception& e) {
        cerr << "Error en NormalG match: " << e.what() << endl;
		exit(1);
    }
}