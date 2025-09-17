#include <iostream>
#include "Board.h"
using namespace std;

void Board::fullMatrix() {

	for (int i = 0; i < 8; i++)
	{

		for (int j = 0; j < 8; j++)
		{
			int type = rand() % 5;//genera un numero entre 0 y 4
			matrix[i][j] = type;
			matrixx[i][j].setTexture(fruits->getTexture(type));//asigna la textura dependiendo del numero asignado a cada posicion, que es el tipo de fruta
			matrixx[i][j].setPosition(j * 64.f, i * 64.f);
			matrixx[i][j].setScale(0.1f, 0.1f);
			
		}
	}
}
bool Board::deleteVertical() {
	bool deleted = false;
	
	for (int j = 0; j < 8; j++)//empieza columna en vez de fila porque es vertical
	{
		int counter = 1;
		for (int  i= 1; i  < 8; i++)
		{
			if (matrix[i][j] == matrix[i - 1][j] && matrix[i][j] != -1) {//si el anterior es igual al actual y el valor no es -1 se suma contador
				counter++;
			}
			else {//si la posicion actual es diferente a la anterior pero el contador es mayor o igual a 3 entonces se eliminan los 3 o mas anteriores
				if (counter >= 3) {
					for (int u = 0; u < counter; u++)
					{
						int indexDelete = (i - 1) - u;
						matrix[indexDelete][j] = -1;
					}
					deleted = true;
					points += 10 * counter;
			
				}
				counter = 1;
			}
		}if (counter >= 3) {//para el caso de que la secuencia llegue hasta el final de la columna
			for (int k = 0; k < counter; k++)
			{
				matrix[7 - k][j] = -1;		
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
		for (int j = 1; j < 8; j++)//empieza en 1 para comparar con el anterior
		{
			if (matrix[i][j] == matrix[i][j - 1] && matrix[i][j] != -1) {
				counter++;
			}
			else {// si la posicion actual es diferente a la anterior pero el contador es mayor o igual a 3 entonces se eliman los 3 o mas anteriores
				if (counter >= 3) {
					for (int v = 0; v < counter; v++) {//recorre la cantidad que se encontró
						int indexDelete = (j - 1) - v;
						matrix[i][indexDelete] = -1;
					}deleted = true;
					points += 10 * counter;//puntos que se van sumando y que luego se pasan a score en Game con un getScore()
					
				}counter = 1;
			}
		}
		if(counter>=3){//para el caso de que la secuencia llegue hasta el final de la fila
			for (int b = 0; b < counter; b++)
			{
				matrix[i][7 - b]=-1;//cambia el valor en la matriz de int a -1
			}deleted = true;
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
			if (matrix[i][j] != -1) {
			window.draw(matrixx[i][j]);
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
			if (val >= 0) {
				matrixx[i][j].setTexture(fruits->getTexture(val));//cambia la textura o foto dependiendo del numero que esté en la matriz de int
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
		//recorre columna por columna
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


