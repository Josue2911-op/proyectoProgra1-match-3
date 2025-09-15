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
			matrixx[i][j].setTexture(fruits->getTexture(type));
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
						int indexDelete = (i - 1) - u;
						matrix[indexDelete][j] = -1;
					//	matrixx[indexDelete][j].setTexture(sf::Texture());
						matrixx[indexDelete][j].setColor(sf::Color::Transparent);
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
				//matrixx[7 - k][j].setTexture(sf::Texture());
				matrixx[7 - k][j].setColor(sf::Color::Transparent);
				
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
						int indexDelete = (j - 1) - v;
						matrix[i][indexDelete] = -1;
					}deleted = true;
					points += 10 * counter;
					
				}counter = 1;
			}
		}
		if(counter>=3){
			for (int b = 0; b < counter; b++)
			{
				matrix[i][7 - b]=-1;
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
			if (matrix[i][j] != -1) {
			window.draw(matrixx[i][j]);
			}
		}
	}
}
void Board::updateSprites() {
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			int val = matrix[i][j];
			if (val >= 0) {
				matrixx[i][j].setTexture(fruits->getTexture(val));
				matrixx[i][j].setColor(sf::Color::White);
				matrixx[i][j].setPosition(j * 64.f, i * 64.f);
				matrixx[i][j].setScale(0.1f, 0.1f);
			}
			else {
				matrixx[i][j].setColor(sf::Color::Transparent);
			}
		}
	}
}
void Board::gravity(){
		
		for (int j = 0; j < 8; j++)
		{
			int empty = 7;
			for (int i = 7; i >= 0; i--)
			{
				if (matrix[i][j] != -1)
				{
					if (empty != i) {
						matrix[empty][j] = matrix[i][j];
						matrix[i][j] = -1;
					}empty--;
				}
			}
			for (int e = empty; e >= 0; e--) {
				matrix[e][j]  = rand() % 5;
			}
					
		}
		updateSprites();
}
void Board:: resetPoints() {
	points = 0;
}


