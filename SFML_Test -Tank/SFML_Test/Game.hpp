#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include <iostream>

using namespace std;
using namespace sf;

class Game {
public:
	sf::RectangleShape player;
	sf::RenderWindow* win = nullptr;
	VertexArray line;

	float MouseX;
	float MouseY;
	CircleShape tir;
	Vector2f pos = player.getPosition();
	Vector2f normal;
	float speed = 10;

	Game(sf::RenderWindow* win) {
		this->win = win;
		player = sf::RectangleShape(Vector2f(64, 64));
		player.setFillColor(Color(0xEB2C4C));
		player.setOutlineColor(Color(0x50F2E4));
		player.setPosition(50, 50);
		player.setOrigin(25, 25);
	}

	void processInput(sf::Event ev) {
		if (ev.type == sf::Event::Closed)
			win->close();
		if (ev.type == sf::Event::KeyReleased) {

		}
		if (ev.type == Event::MouseMoved)
		{
			MouseX = ev.mouseMove.x;
			MouseY = ev.mouseMove.y;
			auto angle = atan2(MouseY - pos.y , MouseX - pos.x) * (180/ 3.14);
			//if (angle < 0) angle = 360 - (-angle);
			//cout << angle << endl;
			player.setRotation(angle);
		}
		//if (Mouse::isButtonPressed(Mouse::Left))
		if (ev.type == Event::MouseButtonPressed)
		{
			tir = CircleShape(10);
			tir.setFillColor(Color(0x0563FA));
			tir.setPosition(pos);

			auto dir = (Vector2f(MouseX, MouseY) - pos);
			normal = dir / sqrt(pow(dir.x, 2) + pow(dir.y, 2));
			cout << normal.x << endl;
		}
	}

	void pollInput() {
		Vector2f ppos = player.getPosition();
		pos = player.getPosition();
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
		player.setPosition(ppos);
		line.clear();
		line.setPrimitiveType(sf::PrimitiveType::Lines);
		line.append(sf::Vertex(ppos, sf::Color(0x5DFFA3ff)));
		line.append(sf::Vertex(Vector2f(MouseX,MouseY), sf::Color(0x5DFFA3ff)));
	}

	void update() {
		pollInput();
		tir.move(normal * speed);

	}

	void draw(sf::RenderWindow& win) {
		win.draw(player);

		win.draw(line);
		win.draw(tir);
	}
};