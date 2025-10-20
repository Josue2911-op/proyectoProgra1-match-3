#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Game.h"
Board* p = new Board();
Game* g = new Game(p);
using namespace std;
void startWindow() {
    sf::RenderWindow window2(sf::VideoMode(800, 600), "Match-3 Start");
    sf::Text textStart;
	sf::Font fontStart;
	fontStart.loadFromFile("BitcountGridDouble_Cursive-Regular.ttf");
    textStart.setFont(fontStart);
    textStart.setString("START");
    textStart.setCharacterSize(50);
    textStart.setFillColor(sf::Color::White);
	textStart.setPosition(350, 250);
    while (window2.isOpen()) {
        sf::Event event2;
        while (window2.pollEvent(event2)) {
            if (event2.type == sf::Event::Closed) {
                window2.close();
            }
            if (event2.type == sf::Event::MouseButtonPressed && event2.mouseButton.button== sf::Mouse::Left) {
                sf::Vector2i mouse2 = sf::Mouse::getPosition(window2);
                if (textStart.getGlobalBounds().contains(mouse2.x, mouse2.y)) { //si se preciona start en la hitbox con click izzquierdo, la ventana cierra 
                    window2.close();                                               // y empieza el juego 
                }
            }
        }
        window2.clear();
        window2.draw(textStart);
        window2.display();
    }
}//copie y pegue lo de arriba para ahorrar tiempo ya que es casi lo mismo

bool endWindow() {
    sf::RenderWindow windowEnd(sf::VideoMode(800, 600), "End screen");
    sf::Text textScore;
    sf::Text textRestart;
    sf::Text textEnd;
    sf::Text congrats;
    sf::Text fail;
    sf::Text next;
    sf::Font fontEnd;

    fontEnd.loadFromFile("BitcountGridDouble_Cursive-Regular.ttf");
    if (g->checkCompleted() && g->getCurrentLevel()<=3) {
        congrats.setFont(fontEnd);
        congrats.setString("Level Completed!!");
        congrats.setCharacterSize(30);
        congrats.setFillColor(sf::Color::White);
        congrats.setPosition(250, 100);
        if (g->getCurrentLevel() < 3) {
            next.setFont(fontEnd);
            next.setString("Next Level");
            next.setCharacterSize(20);
            next.setFillColor(sf::Color::White);
            next.setPosition(350, 150);
        }
    }
    else if (!g->checkCompleted()) {
        fail.setFont(fontEnd);
        fail.setString("Game Over!!");
        fail.setCharacterSize(30);
        fail.setFillColor(sf::Color::White);
        fail.setPosition(300, 100);
    }
    //boton restart
    textRestart.setFont(fontEnd);
    textRestart.setString("Restart");
    textRestart.setCharacterSize(20);
    textRestart.setFillColor(sf::Color::White);
    textRestart.setPosition(350, 200);
	//boton score
    textScore.setFont(fontEnd);
    textScore.setString("Final score: " + to_string(g->getFinalScore()));
    textScore.setCharacterSize(20);
    textScore.setFillColor(sf::Color::White);
	textScore.setPosition(350, 300);
    //boton para terminar
    textEnd.setFont(fontEnd);
    textEnd.setString("End game");
    textEnd.setCharacterSize(20);
    textEnd.setFillColor(sf::Color::White);
    textEnd.setPosition(350, 250);

    while (windowEnd.isOpen()) {
        sf::Event event3;
        while (windowEnd.pollEvent(event3)) {
            if (event3.type == sf::Event::Closed) {
                windowEnd.close();
            }
            if (event3.type == sf::Event::MouseButtonPressed && event3.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mouse3 = sf::Mouse::getPosition(windowEnd);//posicion X y Y del mouse en la ventana
                if (textEnd.getGlobalBounds().contains(mouse3.x, mouse3.y)) {// si se presiona end game en la hitbox de ese texto con el click izquierdo
                    windowEnd.close(); //la ventana se cierra y el main termina retornando false, por ende termina el programa garacias while(restart)
                    return false;
                }
                if (g->checkCompleted() && g->getCurrentLevel() < 3 && next.getGlobalBounds().contains(mouse3.x, mouse3.y)) {
					int level = g->getCurrentLevel()+1;
					g->createDataLevel(level);
                    p->fullMatrix();                                              // se reinicia la matriz, los puntos y movimientos
                    p->resetPoints();
                    g->reset();
                    windowEnd.close();
                    return true;
                }
                if (textRestart.getGlobalBounds().contains(mouse3.x, mouse3.y)) {// si preciona en restart en la hitbox con click izquierdo
                    p->fullMatrix();                                              // se reinicia la matriz, los puntos y movimientos
                    p->resetPoints();
                    g->reset();
                    windowEnd.close();
                    return true;
                }
            }
        }
        windowEnd.clear();
		windowEnd.draw(congrats);
		windowEnd.draw(next);
        windowEnd.draw(fail);
        windowEnd.draw(textRestart);
        windowEnd.draw(textScore);
        windowEnd.draw(textEnd);
        windowEnd.display();
    }
    return false;
}
int main() {
    g->createDataLevel(1);
    bool restart = true;
    while (restart) {
        startWindow();
        sf::Event event;
        sf::RenderWindow window(sf::VideoMode(800, 600), "Match-3");
        p->fullMatrix();
        while (window.isOpen()) {
            bool moved = false;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i pos = g->posMouse(window);
                    moved = g->replacePlace(pos);

                }
            }
            sf::Vector2i lastMove = g->getMove();
            bool check = true;
            while (check) {//mientras se puedan eliminar se sigue haciendo la gravedad
                check = false;
                if (p->deleteVertical(lastMove) || p->deleteHorizontal(lastMove)) {
                    check = true;
                    p->gravity();
                }
            }
            p->animation(0.5f, 2.f);
            window.clear();
            p->show(window);
           window.draw(g->yourScore());
           window.draw(g->objectivesText());
            window.draw(g->yourMoves(moved));
            window.display();

            if (g->getCurrentLevel() == 1 && g->getMoves() == 0) {
                window.close();
            }
            else if (g->getCurrentLevel() == 2 && g->checkCompleted() || g->getMoves() == 0 
                || g->getCurrentLevel() == 3 && g->checkCompleted() || g->getMoves() == 0){
                window.close();
			}
        }
        restart = endWindow();
    }

    return 0;
    delete p;
    delete g;
}