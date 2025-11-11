#include "Ranking.h"
using namespace std;
void Ranking::addScore() {
    try {

        ofstream  archive("assets/LeaderBoard.txt", ios::app);//ios::app indica que todas las escrituras en el archivo se harán al final, sin sobrescribir el contenido existente
                                                     // Incluso si usas seekp() para mover el puntero, el modo app forzará que la escritura ocurra al final
        if (!archive.is_open()) {
            throw runtime_error("No se pudo abrir el archivo LeaderBoard.txt");

        }
        archive << name << "   " << scoreRk<< "\n";
            archive.close();
    }
    catch (const exception& e) {
        cout << "error al guardar en el archivo" << e.what();
    }
}
void Ranking::show() {
	sf::RenderWindow window(sf::VideoMode(800, 600),"LeaderBoard");
    sf::Text textLeaderBoard;
    sf::Text entrada;
    sf::Font fontLeaderBoard;
    try {
        fontLeaderBoard.loadFromFile("assets/BitcountGridDouble_Cursive-Regular.ttf");

    }
    catch (const exception& e) {
        cerr << "Error al cargar la fuente: " << e.what() << endl;
        exit(1);
    }

    textLeaderBoard.setFont(fontLeaderBoard);
    textLeaderBoard.setString("WRITE YOUR USERNAME");
    textLeaderBoard.setCharacterSize(30);
    textLeaderBoard.setFillColor(sf::Color::White);
    textLeaderBoard.setPosition(250, 200);

    entrada.setFont(fontLeaderBoard);
    entrada.setString("");
    entrada.setCharacterSize(25);
    entrada.setFillColor(sf::Color::Yellow);
    entrada.setPosition(350, 300);
    
    ifstream archiveLB("assets/LeaderBoard.txt");

    if (!archiveLB.is_open()) {
        cerr << "Error al abrir LeaderBoard.txt para lectura\n";
        return;
    }
    bool finished = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\r') {// '\r' es el ENTER del teclado, la info se guarda cuando se presiona
                    addScore();// guarda info
                    finished = true;
                    window.close();
                }
                else if (event.text.unicode == 8 && !name.empty()) {//empty funcion libreria string, devuekve true si el string está vacio, osea no tiene caracteres
                    // aca se ejecuta si él string no esta vacio
                    // evente.text.unicode no recibe como tal texto, sino valores enteros, como 8 que es el backspace(tecla de borrar)

                    name.pop_back();//pop_back elimina el ultimo caracter de un string, mas que todo para manejar la tecla Backspace
                    // si el usuario borra se quita la ultima letra ejmplo : hola ->(borra)-> hol.
                }
                else if (event.text.unicode <128 && event.text.unicode != 8) {// < 128 se refiere, valores de tabla ascii, letras del teclado
                    char letter = static_cast<char>(event.text.unicode);// comando de c++ para convertir variables de un tipo a otro, en este caso de enteros a char 
                    name += letter;
                }
            }
        }
        entrada.setString(name);
        window.clear(sf::Color::Black);
        window.draw(textLeaderBoard);
        window.draw(entrada);
        window.display();
    
    }

    if (finished) {
        ifstream archive("assets/LeaderBoard.txt");
        if (!archive.is_open()) {
            cerr << "Error al abrir LeaderBoard.txt para lectura\n";
            return;
        }

        int scores[100];
        string users[100];
        int count = 0;
        while (archive >> users[count] >> scores[count] && count < 100) {
            count++;
        }

        //ordenar por metodo burbuja
        for (int i = 0; i < count-1; i++)
        {
            for (int j = 0; j < count-i-1; j++)
            {
                if (scores[j] < scores[j+1]) {
                    swap(scores[j], scores[j+1]);
                    swap(users[j], users[j + 1]);
                }
            }
        }

        sf::RenderWindow windowLD(sf::VideoMode(800, 600), "top 5 players");
        sf::Text tittle;
        tittle.setFont(fontLeaderBoard);
        tittle.setString("--- TOP 5 LEADERBOARD ----");
        tittle.setCharacterSize(30);
        tittle.setFillColor(sf::Color::Cyan);
        tittle.setPosition(200, 50);
        sf::Text line[5];
        for (int i = 0; i < 5 && i < count; i++)
        {
            line[i].setFont(fontLeaderBoard);
            line[i].setCharacterSize(20);
            line[i].setFillColor(sf::Color::White);
            line[i].setPosition(250,110+i*40);
            line[i].setString(users[i] + "  " + to_string(scores[i]));
        }

        while (windowLD.isOpen()) {
            sf::Event event2;
            while (windowLD.pollEvent(event2)) {
                if (event2.type == sf::Event::Closed ) {
                    windowLD.close();
                }
            }
            windowLD.clear();
            windowLD.draw(tittle);
            for (int i = 0; i < 5 && i < count; i++)
            {
                windowLD.draw(line[i]);
            }  windowLD.display();
        }

    }
}