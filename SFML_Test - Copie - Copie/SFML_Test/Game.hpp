#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

using namespace sf;

class Game {
public:
	sf::RectangleShape player;

	Game() {
		player = sf::RectangleShape(Vector2f(64, 64));
		player.setFillColor(Color(0xEB2C4C));
		player.setOutlineColor(Color(0x50F2E4));
		player.setPosition(50, 50);
		player.setOrigin(25, 25);
	}

	void processInput(sf::Event ev)
	{
		if (ev.type == sf::Event::KeyReleased) {
			
		}
	}

	void pollInput() {
		Vector2f ppos = player.getPosition();
		if (Keyboard::isKeyPressed(Keyboard::Key::Z))
		{
			ppos.y--;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Q))
		{
			ppos.x--;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
		{
			ppos.y++;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
		{
			ppos.x++;
		}
	}

	void update() {
		pollInput();
	}

	void draw(sf::RenderWindow& win) {
		win.draw(player);
	}
};