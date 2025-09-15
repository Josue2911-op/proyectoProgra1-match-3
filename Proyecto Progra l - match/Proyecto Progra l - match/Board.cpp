#include <iostream>
#include "Board.h"
using namespace std;

void Board::fullMatrix() {

	for (int i = 0; i < 8; i++)
	{

		for (int j = 0; j < 8; j++)
		{
			int type = rand() % 5;
			matrix[i][j] = type;
			matrixx[i][j] = fruits->getfruitsImages(type);
			matrixx[i][j].setPosition(j * 64.f, i * 64.f);
			matrixx[i][j].setScale(0.1f, 0.1f);
			
		}
	}
}
bool Board::deleteVertical() {
	bool deleted = false;
	
	for (int j = 0; j < 8; j++)
	{
		int counter = 1;
		for (int  i= 1; i  < 8; i++)
		{
			if (matrix[i][j] == matrix[i - 1][j] && matrix[i][j] != -1) {
				counter++;
			}
			else {
				if (counter >= 3) {
					for (int u = 0; u < counter; u++)
					{
						matrix[(i - 1) - u][j] = -1;
						matrixx[(i - 1) - u][j].setColor(sf::Color(255, 255, 255, 0));
					}
					deleted = true;
					points += 10 * counter;
			
				}
				counter = 1;
			}
		}if (counter >= 3) {
			for (int k = 0; k < counter; k++)
			{
				matrix[7 - k][j] = -1;
				matrixx[7 - k][j].setColor(sf::Color(255, 255, 255, 0));
			}deleted = true;
			points += 10 * counter;
			
		}
	}
	return deleted;
}
bool Board::deleteHorizontal() {

	bool deleted = false;
	for (int i = 0; i < 8; i++)
	{
		int counter = 1;
		for (int j = 1; j < 8; j++)
		{
			if (matrix[i][j] == matrix[i][j - 1] && matrix[i][j] != -1) {
				counter++;
			}
			else {
				if (counter >= 3) {
					for (int v = 0; v < counter; v++) {
						matrix[i][(j - 1) - v] = -1;
						matrixx[i][(j-1)-v].setColor(sf::Color(255, 255, 255, 0));
					}deleted = true;
					points += 10 * counter;
					
				}counter = 1;
			}
		}
		if(counter>=3){
			for (int b = 0; b < counter; b++)
			{
				matrix[i][7 - b]=-1;
				matrixx[i][7-b].setColor(sf::Color(255, 255, 255, 0));
			}deleted = true;
			points += 10 * counter;
		
		}
	}
	return deleted;
}
void Board :: show(sf::RenderWindow& window){
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			window.draw(matrixx[i][j]);

		}
	}
}
void Board::gravity(){
	bool verified = true;
	while (verified) {
		verified = false;
		for (int j = 0; j < 8; j++)
		{
			for (int i = 7; i > 0; i--)
			{
				if (matrix[i][j] == -1)
				{
					matrix[i][j] = matrix[i - 1][j];
					matrix[i - 1][j] = -1;
					matrixx[i][j] = matrixx[i - 1][j];
					matrixx[i][j].setPosition(j * 64.f, i * 64.f);
					verified = true;

				}

			}
			if (matrix[0][j] == -1) {
				int typeGrav = rand() % 5;
				matrix[0][j] = typeGrav;
				matrixx[0][j] = fruits->getfruitsImages(typeGrav);
				matrixx[0][j].setPosition(j * 64.f, 0 * 64.f);
				matrixx[0][j].setScale(0.1f, 0.1f);
				verified = true;
			}

		}
	}
}

