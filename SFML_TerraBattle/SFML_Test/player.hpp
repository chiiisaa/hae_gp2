#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include <iostream>

using namespace std;
using namespace sf;

class player {
public:
	RectangleShape shape;

	Texture text;
	Texture textureSansFond;
	RectangleShape playerTexture;
	

	player() {
		shape = RectangleShape(Vector2f(64, 64));
		//shape.setFillColor(Color(0xEB2C4C));
		shape.setOrigin(25, 25);
		textureSansFond.loadFromFile("images/playerS.PNG");
		shape.setTexture(&textureSansFond);
		
		text.loadFromFile("images/player.PNG");
		playerTexture = RectangleShape(Vector2f(400, 350));
		playerTexture.setFillColor((sf::Color(255, 255, 255, 0)));
		playerTexture.setOrigin(25, 25);
		//playerTexture.setPosition(247, 324);
		playerTexture.setTexture(&text);
	}


	void setPosition(Vector2f pos)
	{
		shape.setPosition(pos);
	}

	void color(Color c)
	{
		shape.setFillColor(c);
	}

	Vector2f getPosition() {
		return shape.getPosition();
	}

	float mul = 0.01;
	bool Attack()
	{
		//cout << shape.getScale().x << endl;
		float size = shape.getScale().x + mul;
		if (shape.getScale().x > 2)
		{
			mul = -0.01;
		}
		shape.setScale(Vector2f(size, size));
		//cout << shape.getScale().x << endl;
		if (shape.getScale().x <= 1)
		{
			cout << "play attack false" << endl;
			mul = 0.01;
			return false;
		}
		return true;
	}

	void limite()
	{
		if (getPosition().x > 485) setPosition(Vector2f(485, getPosition().y));
		if (getPosition().x < 84) setPosition(Vector2f(84, getPosition().y));
		if (getPosition().y > 646) setPosition(Vector2f(getPosition().x, 646));
		if (getPosition().y < 84) setPosition(Vector2f(getPosition().x, 84));
	}

	void draw(sf::RenderWindow& win)
	{
		win.draw(shape);
		//win.draw(playerTexture);
	}
};