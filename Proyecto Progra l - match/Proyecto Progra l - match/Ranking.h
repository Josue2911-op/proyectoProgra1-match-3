#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
class Ranking{
private:
	int scoreRk;
	Game* pt;
	string name;
public:
	Ranking( Game* f): scoreRk(f->getFinalScore()), pt(f), name("") {}

	void addScore();
	void show();
};