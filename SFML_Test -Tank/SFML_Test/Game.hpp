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
	float speed = 10;
	Vector2f pos = player.getPosition();
	Vector2f normal;
	CircleShape tir;
	RectangleShape canon = RectangleShape(Vector2f(60, 10));

	Game(sf::RenderWindow* win) {
		this->win = win;
		player = sf::RectangleShape(Vector2f(64, 64));
		player.setFillColor(Color(0xEB2C4C));
		player.setOutlineColor(Color(0x50F2E4));
		player.setPosition(50, 50);
		player.setOrigin(25, 25);

		canon.setFillColor(Color(0x50F2E4));
	}

	void processInput(sf::Event ev) {
		if (ev.type == sf::Event::Closed)
			win->close();
		if (ev.type == sf::Event::KeyReleased) {

		}
		if (ev.type == Event::MouseMoved)
		{
			//Rotation du joueur 
			MouseX = ev.mouseMove.x;
			MouseY = ev.mouseMove.y;
			double angle = atan2(MouseY - pos.y , MouseX - pos.x) * (180/ 3.14);
			//if (angle < 0) angle = 360 - (-angle);
			//cout << angle << endl;
			player.setRotation(angle);
			canon.setRotation(angle);
		}
		//if (Mouse::isButtonPressed(Mouse::Left))
		if (ev.type == Event::MouseButtonPressed)
		{
			tir = CircleShape(10);
			tir.setFillColor(Color(0x0563FA));
			tir.setPosition(pos);

			// calcul : Longueur Vecteur ||V|| =racine carré de ((Vx * Vx) + (Vy * Vy))
			// normalisé Vecteur : U = V / ||V||
			auto temp = (Vector2f(MouseX, MouseY) - pos);
			normal = temp / sqrt(pow(temp.x, 2) + pow(temp.y, 2));
			cout << normal.x << normal.y << endl;
			cout << temp.x << " Y :"<< temp.y << endl;
		}
	}

	void pollInput() {
		Vector2f ppos = player.getPosition();
		pos = player.getPosition();
		if (Keyboard::isKeyPressed(Keyboard::Key::Z))
		{
			pos.y--;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Q))
		{
			pos.x--;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
		{
			pos.y++;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
		{
			pos.x++;
		}
		limite();

		player.setPosition(pos);
		canon.setPosition(pos);

		//line.clear();
		//line.setPrimitiveType(sf::PrimitiveType::Lines);
		//line.append(sf::Vertex(pos, sf::Color(0x5DFFA3ff)));
		//line.append(sf::Vertex(Vector2f(MouseX,MouseY), sf::Color(0x5DFFA3ff)));
	}

	void limite()
	{
		if (pos.y > 680)
		{
			pos.y = 680;
		}
		if (pos.y < 29)
		{
			pos.y = 29;
		}
		if (pos.x < 30)
		{
			pos.x = 30;
		}
		if (pos.x > 1241)
		{
			pos.x = 1241;
		}
	}

	void update() {
		pollInput();
		tir.move(normal * speed);
	}

	void draw(sf::RenderWindow& win) {
		win.draw(player);
		//win.draw(line);
		win.draw(tir);
		win.draw(canon);
	}

	void rebond(bool rebondOk)
	{

	}
};