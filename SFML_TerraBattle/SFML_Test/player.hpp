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
	
	RectangleShape healthBarBg;
	RectangleShape healthBar;
	float health = 100;
	float Maxhealth = 100;

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

		iniHealth();
	}


	void setPosition(Vector2f pos)
	{
		shape.setPosition(pos);

		this->healthBarBg.setPosition(shape.getPosition());

		this->healthBar.setPosition(shape.getPosition());
	}

	void color(Color c)
	{
		shape.setFillColor(c);
	}

	Vector2f getPosition() {
		return shape.getPosition();
	}

	float mul = 0.05;
	bool Attack()
	{
		float size = shape.getScale().x + mul;
		if (shape.getScale().x > 2)
		{
			mul = -0.05;
		}
		shape.setScale(Vector2f(size, size));
		if (shape.getScale().x <= 1)
		{
			mul = 0.05;
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

	void iniHealth() {
		healthBarBg.setSize(Vector2f(60, 10));
		healthBarBg.setFillColor(Color::Black);
		healthBarBg.setOrigin(Vector2f(22, -17));
		healthBarBg.setPosition(shape.getPosition());

		healthBar.setSize(Vector2f(60, 10));
		healthBar.setFillColor(Color::Yellow);
		healthBar.setOrigin(Vector2f(22, -17));
		healthBar.setPosition(shape.getPosition());
	}

	void updateHp()
	{
		float percent = health / Maxhealth;

		healthBar.setSize(Vector2f(60 * percent, healthBar.getSize().y));
	}

	void looseHp(float degat)
	{
		health -= degat;
		if (health < 0)
		{
			health = 0;
		}
		updateHp();
	}

	void draw(sf::RenderWindow& win)
	{
		win.draw(shape);

		win.draw(healthBarBg);
		win.draw(healthBar);
		//win.draw(playerTexture);
	}
};