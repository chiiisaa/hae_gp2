#pragma once

#include "SFML/Graphics.hpp"
#include "Dice.hpp"

using namespace sf;
class Particle {
public:

	RectangleShape	el;
	float			x = 0.0f;
	float			y = 0.0f;

	float			dx = 0.0f;
	float			dy = 0.0f;

	float			life = 1.0f;

	float			scaleX = 1.0f;
	float			scaleY = 1.0f;

	bool			destroyed = false;

	Particle() {
		el = RectangleShape(Vector2f(8, 8));
		el.setOrigin(4, 4);
		el.setFillColor(sf::Color(0xff0000ff));
		life = Dice::randF() * 6.0 + 2.0 * 6.0;
	}

	void update(float dt) {
		x += dx * dt;
		y += dy * dt;

		el.setPosition(x, y);
		el.rotate(dt * 3.0);

		life -= dt;

		el.setScale(scaleX, scaleY);

		if (life <= 10.0) {
			dx *= 0.98;
			dy *= 0.98;
		}

		if (life <= 20.0) {
			scaleX *= 0.95;
			scaleY *= 0.95;
		}

		if (el.getSize().x <= 0.1 || el.getSize().x <= 0.1) {
			destroyed = true;
		}
	}
};
