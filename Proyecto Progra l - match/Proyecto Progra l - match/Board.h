#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gems.h"
#include "IceGem.h"
#include "PowerGem.h"
#include "normalGem.h"
using namespace std;
class Board {
private:
	int** matrix;
	sf::Sprite **matrixx;
	int points;
	Gems*** matrixG;
public:
	Board() {
		points = 0;
		matrixG = new Gems **[8];
		for (int i = 0; i < 8; i++)
		{
			matrixG[i] = new Gems*[8];
		}
	 Gems::createImages();
		matrixx = new sf::Sprite*[8];
		for (int i = 0; i < 8; i++)
		{
			matrixx[i] = new sf::Sprite[8];
		}

		matrix = new int * [8];

		for (int i = 0; i < 8; i++)
		{
			matrix[i] = new int[8];
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				matrix[i][j] = 0;
			}
		}
		
	}

	void fullMatrix();
	bool deleteVertical(sf::Vector2i pos);
	bool deleteHorizontal(sf::Vector2i movedPos);

	int& getScorePower() {
		return points;
	}
	int getScore() {
		return points;
	}
	void setPoints(int s) {
		points = s;
	}
	sf::Sprite& getMatrixx(int i, int j) {// get matrix para usarla en Game.cpp en replacePlace, recibiendo las 2 matrices de enteros y sprites
											//para hacer el intercambio de posiciones y se validen las eliminaciones en las matrices originales
		return matrixx[i][j];
	}
	int& getMatrix(int i, int j) {
		return matrix[i][j];
	}
	Gems*& getMatrixG(int i, int j) {
		return matrixG[i][j];
	}
	int** getMatrixReplace() {
		return matrix;
	}
	sf::Sprite** getMatrixxReplace() {
		return matrixx;
	}
	Gems*** getMatrixGForReplace() {
		return matrixG;
	}
	void cleanDeletedSprites();
	void createPowerGem(int i, int j);
	void gravity();
	void show(sf::RenderWindow& window);
	void updateSprites();
	void resetPoints();

	~Board() {
		for (int i = 0; i < 8; i++) {
			delete matrixx[i];
		}delete[]matrixx;
		for (int i = 0; i < 8; i++) {
				delete matrix[i];
		} delete[]matrix;
		
	}
};
