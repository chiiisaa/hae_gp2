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

	Texture textureHealer;
	Texture textureSansFond;

	RectangleShape healthBarBg;
	RectangleShape healthBar;
	float health = 100;
	float Maxhealth = 100;

	bool die = false;

	bool healer;

	player(bool H = false) {
		shape = RectangleShape(Vector2f(64, 64));
		//shape.setFillColor(Color(0xEB2C4C));
		shape.setOrigin(25, 25);
		textureSansFond.loadFromFile("images/playerS.PNG");


		textureHealer.loadFromFile("images/playerH.PNG");

		iniHealth();

		healer = H;

		shape.setTexture(&textureSansFond);

		/*if (H)
		{
			shape.setTexture(&textureHealer);
		}
		else shape.setTexture(&textureSansFond);*/
	}

	void SetHealer()
	{
		Maxhealth = 70;
		health = 70;
		shape.setTexture(&textureHealer);
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

	void UpdateHp(float degat)
	{
		health += degat;
		if (health < 0)
		{
			die = true;
			health = 0;
		}
		else if (health >= Maxhealth)
		{
			health = Maxhealth;
		}
		updateHp();
	}

	float time = 1;
	void Degat(float dt)
	{
		time -= dt;
		if (time <= 0.5)shape.setFillColor((sf::Color::Red));
		else if (time <= 0.6)shape.setFillColor((sf::Color::White));
		else if (time <= 0.7)shape.setFillColor((sf::Color::Red));
		else if (time <= 0.8)shape.setFillColor((sf::Color::White));
		else if (time <= 0.9)shape.setFillColor((sf::Color::Red));

	}

	void reset()
	{
		time = 1;
		shape.setFillColor((sf::Color::White));
	}

	void Heal(float dt)
	{
		time -= dt;
		if (time <= 0.4)reset();
		else if (time <= 0.5)shape.setFillColor((sf::Color::Green));
		else if (time <= 0.6)shape.setFillColor((sf::Color::White));
		else if (time <= 0.7)shape.setFillColor((sf::Color::Green));
		else if (time <= 0.8)shape.setFillColor((sf::Color::White));
		else if (time <= 0.9)shape.setFillColor((sf::Color::Green));

		UpdateHp(0.1);
	}

	void draw(sf::RenderWindow& win)
	{
		win.draw(shape);

		win.draw(healthBarBg);
		win.draw(healthBar);
		//win.draw(playerTexture);
	}
};