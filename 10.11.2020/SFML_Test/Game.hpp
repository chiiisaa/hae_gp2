#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Player.hpp"

#include <iostream>


using namespace std;
using namespace sf;

class Game {
public:
	sf::RenderWindow* win = nullptr;

	Player player;

	Game(sf::RenderWindow* win) {
		this->win = win;

		player.setPosition(1280 * 0.5, 720);
	}

	void processInput(sf::Event ev) {
		if (ev.type == sf::Event::Closed)
			win->close();
	}


	void pollInput(double dt) {
		Vector2f pos = player.getPosition();
		float speed = 600;
		if (Keyboard::isKeyPressed(Keyboard::Key::Z))
		{
			pos.y -= dt * speed;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Q))
		{
			pos.x -= dt * speed;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
		{
			pos.y += dt * speed;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
		{
			pos.x += dt * speed;
		}
		player.setPosition(pos);
	}

	void draw(sf::RenderWindow& win) {
		player.draw(win);
	}


	void update(double dt) {
		pollInput(dt);
		player.update(dt);
	}

};
