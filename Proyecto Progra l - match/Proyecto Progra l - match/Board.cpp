#include <iostream>
#include "Board.h"
#include "IceGem.h"
#include "PowerGem.h"
#include "normalGem.h"
using namespace std;

void Board::fullMatrix() {

	for (int i = 0; i < 8; i++)
	{

		for (int j = 0; j < 8; j++)
		{
			int type = rand() % 6;//genera un numero entre 0 y 5
			matrix[i][j] = type;
			if (type == 5) {
				matrixG[i][j] = new IceGem();
			}
			else {
				matrixG[i][j] = new NormalG(type);
			}
			matrixx[i][j] = matrixG[i][j]->getSprite();
			matrixx[i][j].setPosition(j * 64.f, i * 64.f);
			matrixx[i][j].setScale(0.1f, 0.1f);
			
		}
	}
}
void Board::createPowerGem(int i, int j) {
	if (matrixG[i][j]) delete matrixG[i][j];
	matrixG[i][j] = new PowerGem();
	matrix[i][j] = 6;

	sf::Sprite& spr = matrixG[i][j]->getSprite();
	spr.setPosition(j*64.f, i*64.f);
	spr.setScale(0.1f, 0.1f);
	spr.setColor(sf::Color::White);
	matrixx[i][j] = spr;
}
bool Board::deleteVertical(sf::Vector2i pos) {
	bool deleted = false;

	for (int j = 0; j < 8; j++)//empieza columna en vez de fila porque es vertical
	{
		int counter = 1;
		for (int  i= 1; i  < 8; i++)
		{
			if ((matrix[i][j] == matrix[i - 1][j]||matrix[i][j]==5 || matrix[i - 1][j] == 5) && matrix[i][j] != -1) {//si el anterior es igual al actual y el valor no es -1 se suma contador
				counter++;
			}
			else {//si la posicion actual es diferente a la anterior pero el contador es mayor o igual a 3 entonces se eliminan los 3 o mas anteriores
				if (counter >= 3) {
					int segStart = i - counter;
					int segEnd = i- 1;
					int powerPos = segStart + counter / 2;
					for (int p = segStart; p <= segEnd; p++) {
						if (counter >= 4 && p==powerPos) {
							createPowerGem(p, j);
						}
						else if (matrix[p][j] == 5 && matrixG[p][j] != nullptr) {
							matrixG[p][j]->match(p, j, matrix, matrixx, matrixG);
						}
						else if (matrixG[p][j] != nullptr) {
							matrixG[p][j]->match(p, j, matrix, matrixx, matrixG);
						}
						else {
							matrix[p][j] = -1;
						}
					}
					deleted = true;
					points += 10 * counter;
				}
				counter = 1;
			}
		}	if (counter >= 3) {
			int segStart = 8 - counter;
			int segEnd = 7;
			int powerPos = segStart + counter / 2;
			for (int p = segStart; p <= segEnd; p++) {
				if (counter >= 4 && p==powerPos) {
					
					createPowerGem(p, j);
				}
				else if (matrix[p][j] == 5 && matrixG[p][j] != nullptr) {
					matrixG[p][j]->match(p, j, matrix, matrixx, matrixG);
				}
				else if (matrixG[p][j] != nullptr) {
					matrixG[p][j]->match(p, j, matrix, matrixx, matrixG);
				}
				else {
					matrix[p][j] = -1;
				}
			}
			deleted = true;
			points += 10 * counter;
		}
	
	}
	return deleted;
}
bool Board::deleteHorizontal(sf::Vector2i movedPos) {
	bool deleted = false;
	for (int i = 0; i < 8; i++) {
		int counter = 1;
		for (int j = 1; j < 8; j++) {
			if ((matrix[i][j] == matrix[i][j - 1] || matrix[i][j] == 5 || matrix[i][j - 1] == 5) && matrix[i][j] != -1) {
				counter++;
			}
			else {
				if (counter >= 3) {
					int segStart = j - counter;
					int segEnd = j - 1;
					int powerPos = segStart + counter / 2;
					for (int p = segStart; p <= segEnd; p++) {
						if (counter >= 4 && p == powerPos) {
							createPowerGem(i, p);
						}
						else if (matrix[i][p] == 5 && matrixG[i][p] != nullptr) {
							matrixG[i][p]->match(i, p, matrix, matrixx, matrixG);
						}
						else if (matrixG[i][p] != nullptr) {
							matrixG[i][p]->match(i, p, matrix, matrixx, matrixG);
						}
						else {matrix[i][p] = -1;
					}
						
					}
					deleted = true;
					points += 10 * counter;
				}
				counter = 1;
			}
		}
		if (counter >= 3) {
			int segStart = 8 - counter;
			int segEnd = 7;
			int powerPos = segStart + counter / 2;
			for (int p = segStart; p <= segEnd; p++) {
				if (counter >= 4 && p==powerPos) {
					createPowerGem(i, p);
				}
				else if (matrix[i][p] == 5 && matrixG[i][p] != nullptr) {
					matrixG[i][p]->match(i, p, matrix, matrixx, matrixG);
				}
				else if (matrixG[i][p] != nullptr) {
					matrixG[i][p]->match(i, p, matrix, matrixx, matrixG);
				}
				else { matrix[i][p] = -1; }
				
			}
			deleted = true;
			points += 10 * counter;
		}
	}
	return deleted;
}
void Board :: show(sf::RenderWindow& window){
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (matrix[i][j] != -1&& matrixG[i][j]!=nullptr) {
			window.draw(matrixG[i][j]->getSprite());
			}
		}
	}
}
void Board::updateSprites() {//actualiza las posiciones de los sprites en la matriz de sprites o de imagenes
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int val = matrix[i][j];
			if (val == 6 && matrixG[i][j] == nullptr) {
				matrixG[i][j] = new PowerGem();
			}
			if (matrixG[i][j] != nullptr) {
				sf::Sprite& s = matrixG[i][j]->getSprite();
				if (val >= 0) {
					s.setColor(sf::Color::White);
				}
				else {
					s.setColor(sf::Color::Transparent);
				}s.setPosition(j * 64.f, i * 64.f);
				s.setScale(0.1f, 0.1f);
				matrixx[i][j] = s;
			}
			else {
				matrixx[i][j].setColor(sf::Color::Transparent);
			}

		}
	}
}
void Board::cleanDeletedSprites() {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (matrix[i][j] == -1 && matrixG[i][j] != nullptr) {
				delete matrixG[i][j];
				matrixG[i][j] = nullptr;
				matrixx[i][j].setColor(sf::Color::Transparent);
			}
		}
	}
}
void Board::gravity(){
		//recorre columna por columna de abajo hacia arriba
		for (int j = 0; j < 8; j++)
		{
			int empty = 7;// empieza en la ultima fila
			for (int i = 7; i >= 0; i--)
			{
				if (matrix[i][j] != -1)//si la posicion no hay -1 y si empty es diferente de i, se mueve el valor a la posicion empty
										//e i se vuelve -1, luego empty decrementa
				{
					if (empty != i) {
						matrix[empty][j] = matrix[i][j];
						matrix[i][j] = -1;
						swap(matrixG[empty][j], matrixG[i][j]);
					}empty--;
				}
			}
			for (int e = empty; e >= 0; e--) {// una vez terminado los espacios vacios se llenan con numeros aleatorios 
				
				int type2	= rand() % 6;
				matrix[e][j] = type2;
				if (matrixG[e][j] != nullptr) {
				delete matrixG[e][j];
				matrixG[e][j] = nullptr;
				}matrixG[e][j] = new NormalG(type2);
			}
			updateSprites();
		}
}
void Board:: resetPoints() {
	points = 0;
}