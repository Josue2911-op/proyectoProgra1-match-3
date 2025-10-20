#include "Game.h"
sf::Vector2i Game::posMouse(sf::RenderWindow& window) {// el & es para pasar la referencia de la ventana y no una copia
	                                                    //por ende estamos trabajando con la misma ventana
	sf::Vector2i mouse = sf::Mouse::getPosition(window);
	in1 = mouse.x / 64;// dividido entre 64 para estar en la matriz de las fotos, por ejemolo pos (150,300), 150/64= 2 "columna 2" y lo mismo con y
	in2 = mouse.y / 64;
	if (in1 >= 0 && in1 < 8 && in2 >= 0 && in2 < 8) {
		return { in1,in2 };//devuelve la posicion en la matriz
	}
	else {
		return{ -1,-1 };//esá afuera de la matriz, no se hace nada 
	}

}
bool Game::replacePlace(sf::Vector2i pos) {
	bool moved = false;
	
	 
	if (pos.x == -1 || pos.y== -1) {
		countClicks = 0;
		return false;
	}
	if (countClicks == 0) {
		firstClick = { pos };//guarda la posicion del primer click
		countClicks++;
	}
	else if (countClicks == 1) {
		secondClick = { pos };//guarda el segundo click

		/*abs para ver si estan adyacentes,si la diferencia de "x" y "y" es de 1, manejando verticales y horizontales */
		if (abs(firstClick.x - secondClick.x) == 1 && firstClick.y == secondClick.y || abs(firstClick.y - secondClick.y) == 1 && firstClick.x == secondClick.x) {
			//intercambio logica que utilizamos en una matriz de int.
			if (m->getMatrix(firstClick.y, firstClick.x) == 5 || m->getMatrix(secondClick.y, secondClick.x) == 5) {
				countClicks = 0;
				return false;
			}
			temp1 = m->getMatrix(firstClick.y, firstClick.x);
			m->getMatrix(firstClick.y, firstClick.x) = m->getMatrix(secondClick.y, secondClick.x);
			m->getMatrix(secondClick.y, secondClick.x) = temp1;

			Gems* tempGem = m->getMatrixG(firstClick.y, firstClick.x);
			m->getMatrixG(firstClick.y, firstClick.x) = m->getMatrixG(secondClick.y, secondClick.x);
			m->getMatrixG(secondClick.y, secondClick.x) = tempGem;

			if (m->getMatrixG(firstClick.y, firstClick.x)) {
				m->getMatrixG(firstClick.y, firstClick.x)->targetPos = sf::Vector2f(firstClick.x * 64.f, firstClick.y * 64.f);
			}
			m->getMatrixG(secondClick.y, secondClick.x)->targetPos = sf::Vector2f(secondClick.x * 64.f, secondClick.y * 64.f);
			
			bool check2 = true;

			while (check2) {
				check2 = false;
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						if (m->deleteHorizontal({ j,i }) || m->deleteVertical({ j,i })) {// si se cumple alguna de las condiciones de eliminacion se deja asi y se aplica la gravedad
							check2 = true;
							moved = true;
						}
					}
				}if (check2) {
					m->cleanDeletedSprites();
					m->gravity();
				}
			}
			Gems* gem = m->getMatrixG(firstClick.y, firstClick.x);
			if (gem && m->getMatrix(firstClick.y, firstClick.x) == 6) {
				gem->match(firstClick.y, firstClick.x, m->getMatrixReplace(), m->getMatrixxReplace(), m->getMatrixGForReplace());
				m->cleanDeletedSprites();
				m->gravity();
				m->setPoints(m->getScore() + (8 + 8 - 1) * 10);
				moved = true;
			}
			if(!moved) {// si no se cumple pues vuelven a su lugar haciendo el mismo proceso pero al reves.

						//logica de intercambio pero a la inversa en matriz de int.
						m->getMatrix(secondClick.y, secondClick.x) = m->getMatrix(firstClick.y, firstClick.x);
						m->getMatrix(firstClick.y, firstClick.x) = temp1;

						m->getMatrixG(secondClick.y, secondClick.x) = m->getMatrixG(firstClick.y, firstClick.x);
						m->getMatrixG(firstClick.y, firstClick.x) = tempGem;
						
						m->getMatrixG(firstClick.y, firstClick.x)->targetPos = sf::Vector2f(firstClick.x * 64.f, firstClick.y * 64.f);
						m->getMatrixG(secondClick.y, secondClick.x)->targetPos = sf::Vector2f(secondClick.x * 64.f, secondClick.y * 64.f);
					
						m->getMatrixG(secondClick.y, secondClick.x)->targetPos = sf::Vector2f(secondClick.x * 64.f, secondClick.y * 64.f);
						m->getMatrixG(firstClick.y, firstClick.x)->targetPos = sf::Vector2f(firstClick.x * 64.f, firstClick.y * 64.f);
						
			}
			
		}countClicks = 0;
		

	}
	return moved;
}
sf::Text Game::yourMoves(bool moved) {
	// esto va relacionado con lo que devuelva el metodo replacePlace
	if (moves > 0 && moved) {
			moves -= 1;
	}			
	textMoves.setFont(font2);
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
void Game::createDataLevel(int level) {
	 currentLevel = level;
	reset();
	redCollected = 0;
	iceCubeCollected = 0;
	powerCollected = 0;
	switch (level) {
		case 1:
		redTarget = 0;
		iceObjective = 0;
		powerTarget = 0;
		scoreTarget = 0;
		break;
		case 2:
		redTarget = 15;
		iceObjective = 5;
		powerTarget = 3;
		break;
		case 3:
		scoreTarget = 1000;
		redTarget = 0;
		iceObjective = 0;
		powerTarget = 0;
		break;
	}
}
bool Game::checkCompleted() {
	//verificar si se cumplieron los objetivos
	if (currentLevel == 1) {
		return true;
	}else if (currentLevel == 2) {
		if(redCollected>=redTarget && iceCubeCollected >=iceObjective && powerCollected>=powerTarget) {
			return true;
			
		}
		return false;
	}else if (currentLevel == 3) {
		return score >= scoreTarget;
	}
 return true; 
}
sf::Text Game::objectivesText() {
	objectives.setFont(font);
	objectives.setCharacterSize(18);
	objectives.setFillColor(sf::Color::White);
	objectives.setPosition(520, 110);

	 redCollected += m->getReds();
	 iceCubeCollected += m->getDeleteIce();
	 powerCollected += m->getDeletePower();
	if (currentLevel == 1) {
		stri="Maximize Your Score!!";
	}
	else if (currentLevel == 2) {
		stri= "Destroy Red Gems: " + to_string(redCollected) + " / "+ to_string(redTarget) + "\n" + "Ice Cubes: " + to_string(iceCubeCollected) + "/"
			+ to_string(iceObjective) + "\n" +	"Power Gems: " + to_string(powerCollected) + "/" + to_string(powerTarget);
	}
	else if (currentLevel == 3) {
		stri="Get 1000 points before moves 9 moves : " + to_string(score) + " / " + to_string(scoreTarget) + "\n" +
			"Moves left: " + to_string(moves-10);
	}
	objectives.setString(stri);
	return objectives;
}
int Game:: getFinalScore() {
	return score;
}
int Game::getMoves() {
	return moves;
}
int Game::getCurrentLevel() {
	return currentLevel;
}
void Game:: reset() {
	score = 0;
	powerCollected = 0;
	redCollected = 0;	
	iceCubeCollected = 0;
	moves = 20;
}