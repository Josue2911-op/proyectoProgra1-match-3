#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
class Game {
private:
	Gems* fruits;
	Board* m=nullptr;
	int moves;
	int score;
	sf::Text textScore;
	sf::Text textMoves;
	sf::Font font;
	sf::Font font2;
	int countClicks = 0;
	sf::Vector2i firstClick;
	sf::Vector2i secondClick;
	int temp1;
	sf::Sprite temp2;
	int in1, in2;
public:
	Game(Board* board){
		in1 = 0;
		in2 = 0;
		fruits = new Gems();
		temp1 = 0;
		countClicks = 0;
		m = board;
		moves = 20;
		score = 0;
		font.loadFromFile("BitcountGridDouble_Cursive-Regular.ttf");
		font2.loadFromFile("BitcountGridDouble_Cursive-Regular.ttf");
	}
	sf::Vector2i posMouse(sf::RenderWindow& window);
	bool replacePlace(sf::Vector2i pos);
	sf::Text yourMoves(bool moved);
	sf::Text yourScore();
	int getFinalScore();
	int getMoves();
	void reset();
};