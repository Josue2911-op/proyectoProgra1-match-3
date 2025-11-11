#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

/*Vector2i:es una clase que representa un vector en 2D con componentes de punto entero, mas que todo para posiciones en la matriz, como filas y columnas. 

Vector2f: es una clase que representa un vector en 2D con componentes de punto float, mas que todo para posiciones y movimientos en la ventana con imagenes.

Vector2u: es una clase que representa un vector en 2D con componentes de punto sin signo, mas que todo para dimensiones como ancho y altura de la ventana en la que no son negativos.

*/

class Gems {
protected:
	static sf::Texture textures[8];

public:
	sf::Vector2f targetPos;
	sf::Sprite sprite;
	float fade = 255.f; // Valor inicial de opacidad
	bool fading = false; 
	Gems():fading(false), fade(255.f),targetPos(0.f, 0.f) {
	}
	sf::Texture& getTexture(int index) {//devuelve la textura que se usa en Board para FullMatrix y updateSprites
		return textures[index];//el index es el tipo de gema que esta asignado por el numero random de entre las 5 
	}
	virtual int getType() = 0;
	virtual sf::Sprite& getSprite() = 0;
	virtual void match(int i,int j,int** matrix,sf::Sprite** matrixx, Gems***matrixG)=0;
	static void createImages();

	//intento de crear el fade out, pero no lo logro hacer que funcione correctamente
	void fadeOut() {
		if (!fading) {
			fading = true;
			fade = 255.f;
		
			sf::Sprite& s = this->getSprite();        // usa el sprite de la subclase
			s.setColor(sf::Color(255, 255, 255, 255));
		}
	}

	//intento de crear el fade out, pero no lo logro hacer que funcione correctamente
	void updateFade(float fadeSpeed) {
		if (fading) {
			fade -= fadeSpeed;
			if (fade < 0) fade = 0;
			sf::Color col = sprite.getColor();
			col.a = static_cast<sf::Uint8>(fade);
			sprite.setColor(col);
		  sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(fade)));
		}
		//cout << fade << endl; para ver cual es el valor de fade en consola a ver si funciona(no funciona) 
	}
	bool fadeFinished() {
		return fading && fade <= 0;
	}
	~Gems() {
		
		
	}
};