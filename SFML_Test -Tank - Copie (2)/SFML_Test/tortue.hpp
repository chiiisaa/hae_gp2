#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

enum Cmd {
	Advance,
	Backward,
	TurnLeft45,
	TurnRight45,
};


class tortue {

public:
	float				angle = 0;
	sf::CircleShape		shape;
	sf::RectangleShape	direction;

	tortue() {
		shape = sf::CircleShape(64);
		shape.setFillColor(sf::Color(0xF57F5Dff));
		shape.setOutlineColor(sf::Color(0x59EB7Fff));
		shape.setOutlineThickness(2);
		shape.setPosition(400, 400);
		shape.setOrigin(32, 32);

		direction = sf::RectangleShape(Vector2f(64, 8));
		direction.setFillColor(sf::Color(0xffffffff));
		direction.setOutlineColor(sf::Color(0x000000ff));
		direction.setOutlineThickness(2);
		direction.setOrigin(4, 4);
	}

	sf::Vector2f getPosition() {
		return shape.getPosition();
	}

	float DEG_TO_RAD = 1.0 / 360 * 2 * 3.141569;//on ramene le nombre entre 0 et 1 
	float RAD_TO_DEG = 1.0 / 2 * 3.141569 * 360;

	void draw(sf::RenderWindow& win) {
		angle = fmodf(angle, 360);
		win.draw(shape);
		win.draw(direction);
	}

	void setPosition(sf::Vector2f pos) {
		shape.setPosition(pos);
		pos.x += 32;//on peut ecrire dans pos, il est passé par copie, donc la translation ne remontera pas dans game
		pos.y += 32;
		direction.setPosition(pos);
	}

	Vector2f directionFromAngle(float angle) {
		Vector2f dir;
		dir.x = cos(angle * DEG_TO_RAD);
		dir.y = sin(angle * DEG_TO_RAD);
		return dir;
	}

	void advance2(int nbPixel) {
		sf::Transform mat;
		mat.rotate(angle);
		sf::Vector2f move(nbPixel, 0);
		Vector2f moveTransformed = mat.transformPoint(move);

		sf::Vector2f pos = getPosition();
		pos.x += moveTransformed.x;
		pos.y += moveTransformed.y;
		setPosition(pos);
	};

	void advance(int nbPixel) {
		sf::Vector2f pos = getPosition();
		sf::Vector2f dir = directionFromAngle(angle);
		dir.x *= nbPixel;
		dir.y *= nbPixel;
		pos.x += dir.x;
		pos.y += dir.y;
		setPosition(pos);
	}

	void backward(int nbPixel) {
		advance(-nbPixel);
	}

	void turnLeft(float angle) {
		this->angle += angle;
		direction.setRotation(this->angle);
	}

	void turnRight(float angle) {
		this->angle += angle;
		direction.setRotation(this->angle);
	}

	void reset()
	{
		angle = 0;
		shape.setPosition(400, 400);
		direction.setRotation(angle);
	}

	void play(std::vector<Cmd> execute) {
		for (Cmd& cmd : execute) {
			switch (cmd)
			{
			case Advance:advance(30);		  break;
			case Backward:backward(30);		  break;
			case TurnLeft45:turnLeft(45);	  break;
			case TurnRight45:turnRight(45);	  break;
			default:
				break;
			}
		}
	}
};
