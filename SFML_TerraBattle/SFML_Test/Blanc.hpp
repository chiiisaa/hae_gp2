#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

using namespace std;
using namespace sf;

class Blanc {
public:
	RectangleShape shape;

	Blanc() {
		shape = RectangleShape(Vector2f(249, 81));
		shape.setFillColor(Color(0x421737));
		shape.setFillColor((sf::Color(255, 255, 255, 0)));
		shape.setOrigin(96, 32);
		shape.setPosition(Vector2f(325, 407));
		bStart();
	}

	void bStart()
	{
		shape.setFillColor((sf::Color(255, 255, 255, 0)));
		shape.setPosition(Vector2f(325, 407));
	}

	void setShape(bool horizontal)
	{
		if (horizontal) {
			shape = RectangleShape(Vector2f(249, 81));
			shape.setScale(Vector2f(20, 20));
			shape.setOrigin(96, 32);
		}
		else
		{
			shape = RectangleShape(Vector2f(81, 249));
			shape.setScale(Vector2f(20, 20));
			shape.setOrigin(32, 96);
		}
	}
	
	bool bTransition()
	{
		shape.setFillColor((sf::Color(255, 255, 255, 100)));
		Vector2f bScale = shape.getScale();
		if (bScale.y < 9 || bScale.x < 9) shape.setScale(bScale.x - 0.1, bScale.y - 0.1);
		else shape.setScale(bScale.x - 1, bScale.y - 1);
		if (bScale.y > 1 || bScale.x > 1) return true;
		else
		{
			bStart();
			return false;
		}

	}

	void setPos(Vector2f pos)
	{
		shape.setPosition(pos);
	}

	void draw(sf::RenderWindow& win)
	{
		win.draw(shape);
	}
};
