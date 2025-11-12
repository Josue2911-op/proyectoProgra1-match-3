#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Game.h"
#include "Ranking.h"
//what() es un método de la clase std::exception (y sus derivadas) que devuelve un mensaje descriptivo del error.
Board* p = new Board();
Game* g = new Game(p);
using namespace std;
void startWindow() {
    sf::RenderWindow window2(sf::VideoMode(800, 600), "Match-3 Start");
    sf::Text textStart;
	sf::Font fontStart;
    try {
        fontStart.loadFromFile("assets/BitcountGridDouble_Cursive-Regular.ttf");
    }catch(const exception& e) {
        cerr << "Error al cargar la fuente: " << e.what() << endl;
        exit(1);
	}
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
            try {
                if (event2.type == sf::Event::MouseButtonPressed && event2.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse2 = sf::Mouse::getPosition(window2);
                    if (textStart.getGlobalBounds().contains(mouse2.x, mouse2.y)) { //si se preciona start en la hitbox con click izzquierdo, la ventana cierra 
                        window2.close();                                               // y empieza el juego 
                    }
                }
            }
            catch (const exception& e) {
				cerr << "Error en eventos del mouse: " << e.what() << endl;
                exit(1);
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
    sf::Text textSelectLevel;
    try{
        fontEnd.loadFromFile("assets/BitcountGridDouble_Cursive-Regular.ttf");
    }
    catch (const exception& e) {
        cerr << "Error al cargar la fuente: " << e.what() << endl;
        exit(1);
	}
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

    textSelectLevel.setFont(fontEnd);
    textSelectLevel.setString("Select Level");
    textSelectLevel.setCharacterSize(20);
    textSelectLevel.setFillColor(sf::Color::White);
    textSelectLevel.setPosition(350, 350);

    while (windowEnd.isOpen()) {
        sf::Event event3;
        while (windowEnd.pollEvent(event3)) {
            if (event3.type == sf::Event::Closed) {
                windowEnd.close();
            }try{
                if (event3.type == sf::Event::MouseButtonPressed && event3.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse3 = sf::Mouse::getPosition(windowEnd);//posicion X y Y del mouse en la ventana
                    if (textEnd.getGlobalBounds().contains(mouse3.x, mouse3.y)) {// si se presiona end game en la hitbox de ese texto con el click izquierdo
                        windowEnd.close(); //la ventana se cierra y el main termina retornando false, por ende termina el programa garacias while(restart)
                        return false;
                    }
                    if (g->checkCompleted() && g->getCurrentLevel() < 3 && next.getGlobalBounds().contains(mouse3.x, mouse3.y)) {
                        int level = g->getCurrentLevel() + 1;
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

                    if (textSelectLevel.getGlobalBounds().contains(mouse3.x, mouse3.y)) {
                        windowEnd.close();

                        // Abrir la ventana del menú de niveles
                        sf::RenderWindow levelWindow(sf::VideoMode(800, 600), "Select Level");
                        vector<LevelData> levels = g->loadLevels("assets/levels.txt");

                        int lastCompleted = g->getCurrentLevel() - 1;

                        int selectedLevel = g->levelMenu(levelWindow, levels, lastCompleted);

                        if (selectedLevel != -1) {
                            g->createDataLevel(selectedLevel + 1);
                            p->fullMatrix();
                            p->resetPoints();
                            g->reset();
                        }

                        return true; // volvemos al juego
                    }
                }
              
            }
            catch (const exception& e) {
                cerr << "Error en eventos del mouse: " << e.what() << endl;
                exit(1);
            }
        }
       
        windowEnd.clear();
		windowEnd.draw(congrats);
		windowEnd.draw(next);
        windowEnd.draw(fail);
        windowEnd.draw(textRestart);
        windowEnd.draw(textScore);
        windowEnd.draw(textEnd);
        windowEnd.draw(textSelectLevel);
        windowEnd.display();
    }
    return false;
}
int main() {
    // cargar los niveles desde un archivo JSON o .txt
    vector<LevelData> niveles = g->loadLevels("assets/levels.txt");

    // (este método ya crea su propia ventana y devuelve el nivel seleccionado)
    sf::RenderWindow menuWindow(sf::VideoMode(800, 600), "Seleccionar Nivel");
    int nivelSeleccionado = g->levelMenu(menuWindow, niveles, 0); // 0 = solo nivel 1 desbloqueado

 //si el usuario cierra el menu sin elegir
    if (nivelSeleccionado == -1)
        return 0;

    // Paso 4: inicializar el nivel elegido
    g->createDataLevel(nivelSeleccionado + 1);
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
        Ranking rk(g);
        rk.show();
        restart = endWindow();
    }

    return 0;
    delete p;
    delete g;
}