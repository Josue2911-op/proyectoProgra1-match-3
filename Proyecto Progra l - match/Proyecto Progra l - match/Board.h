#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gems.h"
#include "IceGem.h"
#include "PowerGem.h"
#include "normalGem.h"
//#include <cmath>
using namespace std;
class Board {
private:
	int** matrix;
	sf::Sprite** matrixx;
	int points;
	Gems*** matrixG;
	int reds;
		
public:
	int static deleteIce, deletePower;
	Board(){
		reds = 0;
		deleteIce = 0;
		deletePower = 0;
		points = 0;
		try {
			matrixG = new Gems * *[8];
			for (int i = 0; i < 8; i++)
			{
				matrixG[i] = new Gems * [8];
			}
			Gems::createImages();
			matrixx = new sf::Sprite * [8];
			for (int i = 0; i < 8; i++)
			{
				matrixx[i] = new sf::Sprite[8];
			}

			matrix = new int* [8];

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
		catch (const exception& e) {
			cerr<<"Error al asignar memoria en el constructor: "<<e.what() << endl;
			exit(EXIT_FAILURE);
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
	int getReds() {
		int temp = reds;
		reds = 0;
		return temp;
	}
	int getDeleteIce() {
		int temp = deleteIce;
		deleteIce = 0;
		return temp;
	}
	int getDeletePower() {
		int temp = deletePower;
		deletePower = 0;
		return temp;
	}
	void cleanDeletedSprites();
	void createPowerGem(int i, int j);
	void animation(float speed,float fadeSpeed);
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
