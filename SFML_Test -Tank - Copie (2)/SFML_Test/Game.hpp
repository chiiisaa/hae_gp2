#pragma once

#include <vector>;

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "tortue.hpp"


using namespace sf;

class Game {
public:

	sf::RenderWindow* win = nullptr;
	tortue				turtle;

	sf::RectangleShape  bg;
	sf::Texture			tex;

	bool				closing = false;


	Game(sf::RenderWindow* win) {
		this->win = win;
		bg = sf::RectangleShape(Vector2f(win->getSize().x, win->getSize().y));

		bool isOk = tex.loadFromFile("res/bg.jpg");
		if (!isOk) {
			printf("ERR : LOAD FAILED\n");
		}
		bg.setTexture(&tex);
		bg.setSize(sf::Vector2f(1280, 720));
	}

	void processInput(sf::Event ev);

	bool wasPressed = false;


	void pollInput(double dt);
	void onSpacePressed();

	void update(double dt) {
		pollInput(dt);

		beforeParts.update(dt);
		afterParts.update(dt);
	}

	void draw(sf::RenderWindow& win) {
		if (closing) return;

		win.draw(bg);

		beforeParts.draw(win);

		turtle.draw(win);

		afterParts.draw(win);
	}
};