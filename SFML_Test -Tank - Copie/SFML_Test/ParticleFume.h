#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;
class ParticleFume
{
public:
	RectangleShape part;

	float PosX;
	float PosY;

	float life = 3;

	float scaleX = 4.0f;
	float scaleY = 4.0f;

	bool destroy;

	ParticleFume()
	{
		part = RectangleShape(Vector2f(5, 5));
		part.setFillColor(Color(0xE9E6FA));
		part.setOrigin(0, 0);
	}

	void update(double dt)
	{

		part.setPosition(PosX, PosY);
		life -= dt;

		part.setScale(scaleX, scaleY);

		if (life <= 0.2) {
			scaleX *= 0.9;
			scaleY *= 0.9;
		}

		if (part.getScale().x <= 0.1) destroy = true;


	}

};

