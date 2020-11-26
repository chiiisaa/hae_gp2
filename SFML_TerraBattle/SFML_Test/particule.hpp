#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class particule
{
public:
	RectangleShape part;

	float PosX;
	float Posy;

	float scaleX = 1.00f;
	float scaleY = 1.00f;

	float life = 2;

	bool destroy;

	particule()
	{
		part = RectangleShape(Vector2f(60, 60));
		Color col = Color(0xE9E6FA);
		part.setFillColor((sf::Color(col.r, col.g, col.b, 15)));
		part.setOrigin(25, 25);
	}

	void update(double dt)
	{
		part.setPosition(PosX, Posy);
		limite();
		life -= dt;

		part.setScale(scaleX, scaleY);

		if (life <= 0.2) {
			scaleX *= 0.9;
			scaleY *= 0.9;
		}
		if (part.getScale().x <= 0.1) destroy = true;
	}

	void limite()
	{
		if (part.getPosition().x > 485) part.setPosition(Vector2f(485, part.getPosition().y));
		if (part.getPosition().x < 84) part.setPosition(Vector2f(84, part.getPosition().y));
		if (part.getPosition().y > 646) part.setPosition(Vector2f(part.getPosition().x, 646));
		if (part.getPosition().y < 84) part.setPosition(Vector2f(part.getPosition().x, 84));
	}
};
