#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gems.h"
using namespace std;
class Board {
private:
	int** matrix;
	sf::Sprite **matrixx;
	Gems* fruits;
	int points;
public:
	Board() {
		
		points = 0;
	 fruits = new Gems();

	 fruits->createImages();
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
	bool deleteVertical();
	bool deleteHorizontal();

	int getScore() {
		return points;
	}
	sf::Sprite& getMatrixx(int i, int j) {
		return matrixx[i][j];
	}
	int& getMatrix(int i, int j) {
		return matrix[i][j];
	}
	void gravity();
	void show(sf::RenderWindow& window);
	//sf::Vector2i posMouse(sf::RenderWindow window);
	void updateSprites();
	void resetPoints();
};
