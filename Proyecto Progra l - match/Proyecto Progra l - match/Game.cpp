#include "Game.h"
sf::Vector2i Game::posMouse(sf::RenderWindow& window) {
	sf::Vector2i mouse = sf::Mouse::getPosition(window);
	in1 = mouse.x / 64;// dividido entre 64 para estar en la matriz de las fotos
	in2 = mouse.y / 64;
	if (in1 >= 0 && in1 < 8 && in2 >= 0 && in2 < 8) {
		return { in1,in2 };
	}
	else {
		return{ -1,-1 };
	}

}
bool Game::replacePlace(sf::Vector2i pos) {
	bool moved = false;
	
	 
	if (pos.x == -1 || pos.y== -1) {
		countClicks = 0;
		return false;
	}
	if (countClicks == 0) {
		firstClick = { pos };
		countClicks++;
	}
	else if (countClicks == 1) {
		secondClick = { pos };

		if (abs(firstClick.x - secondClick.x) == 1 && firstClick.y == secondClick.y  || abs(firstClick.y - secondClick.y) == 1 && firstClick.x == secondClick.x ) {
			//intercambio logica que utilizamos en una matriz de int.
			temp1 = m->getMatrix(firstClick.y, firstClick.x);
			m->getMatrix(firstClick.y, firstClick.x) = m->getMatrix(secondClick.y, secondClick.x);
			m->getMatrix(secondClick.y, secondClick.x) = temp1;
			//ahora matriz de fotos.

			temp2 = m->getMatrixx(firstClick.y, firstClick.x);
			m->getMatrixx(firstClick.y, firstClick.x) = m->getMatrixx(secondClick.y, secondClick.x);
			m->getMatrixx(secondClick.y, secondClick.x) = temp2;

			//cambiamos las fotos de lugar
			m->getMatrixx(firstClick.y, firstClick.x).setPosition(firstClick.x * 64.f, firstClick.y * 64.f);
			m->getMatrixx(secondClick.y, secondClick.x).setPosition(secondClick.x * 64.f, secondClick.y * 64.f);
			if (m->deleteHorizontal() || m->deleteVertical()) {
				moved = true;
			}
			else {// si no se cumple pues vuelven a su lugar haciendo el mismo proceso pero al reves.

				//logica de intercambio pero a la inversa en matriz de int.
				m->getMatrix(secondClick.y, secondClick.x) = m->getMatrix(firstClick.y, firstClick.x);
				m->getMatrix(firstClick.y, firstClick.x) = temp1;
				// intercambio en matriz de fotos.
				m->getMatrixx(secondClick.y, secondClick.x) = m->getMatrixx(firstClick.y, firstClick.x);
				m->getMatrixx(firstClick.y, firstClick.x) = temp2;
				//posicion original de las fotos.

				m->getMatrixx(secondClick.y, secondClick.x).setPosition(secondClick.x * 64.f, secondClick.y * 64.f);
				m->getMatrixx(firstClick.y, firstClick.x).setPosition(firstClick.x * 64.f, firstClick.y * 64.f);
				moved = false;
			}
		}countClicks = 0;
		

	}
	return moved;
}
sf::Text Game::yourMoves(bool moved) {
	// esto va relacionado con lo que devuelva el metodo replacePlace
	if (moves > 0 && moved) {
			moves -= 1;
	}				textMoves.setFont(font2);
	textMoves.setString("Moves: " + to_string(moves));
	textMoves.setCharacterSize(24);
	textMoves.setFillColor(sf::Color::White);
	textMoves.setPosition(520, 80);
	return textMoves;
}
sf::Text Game::yourScore(){
		score = m->getScore();
		textScore.setFont(font);
		textScore.setString("Score: " + to_string(score));
		textScore.setCharacterSize(24);
		textScore.setFillColor(sf::Color::White);
		textScore.setPosition(520, 50);
		return textScore;
	//hacer el text de sfml para mostrar el score y con un to_string(score) mostrarlo
	// lo mismo con los moves
}
int Game:: getFinalScore() {
	return score;
}
int Game::getMoves() {
	return moves;
}
void Game:: reset() {
	score = 0;
	moves = 20;
}