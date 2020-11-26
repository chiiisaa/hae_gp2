#pragma once

#include <iostream> 
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>


using namespace std;
using namespace sf;

enum Cmd {
	Advance,
	Backward,
	TurnLeft45,
	TurnRight45,
};

class tortue {
public:
	RenderWindow* win = nullptr;
	CircleShape player;

	CircleShape tempPos;

	RectangleShape a;
	Vector2f position = player.getPosition();
	Vector2f direction;
	float angle = 0;

	float DEG_TO_RAD = 1.0 / 360 * 2 * 3.141569;


	tortue() {
		player = CircleShape(50);
		player.setFillColor(Color::Green);
		player.setOrigin(25, 25);
		player.setPosition(50, 50);

		a = RectangleShape(Vector2f(60, 10));
		a.setFillColor(Color(0x50F2E4));
		a.setOrigin(0, 0);
		a.setPosition(player.getOrigin()+ Vector2f(50,50));
	}

	void avancer(int val)
	{
		position = player.getPosition();
		direction = directionFromAngle(angle);
		direction.x *= val;
		direction.y *= val;

		position.x += direction.x;
		position.y += direction.y;

		player.setPosition(position);
		a.setPosition(player.getOrigin() + position);
	}

	void reculer(int val)
	{
		avancer(-val);
	}

	void turnLeft()
	{
		angle -= 45;
		a.setRotation(angle);
	}

	void turnRight()
	{
		angle += 45;
		a.setRotation(angle);
	}

	Vector2f directionFromAngle(float angle) {
		Vector2f dir;
		dir.x = cos(angle * DEG_TO_RAD);
		dir.y = sin(angle * DEG_TO_RAD);
		return dir;
	}

	void draw(sf::RenderWindow& win) {
		win.draw(player);
		win.draw(a);
	}

	void reset()
	{
		angle = 0;
		player.setPosition(400, 400);
		a.setPosition(player.getOrigin() + player.getPosition());
		a.setRotation(angle);
	}

	Vector2f getpos()
	{
		return player.getPosition();
	}

	void setPos(Vector2f pos)
	{
		return player.setPosition(pos);
	}

	void play(std::vector<Cmd> execute) {
		for (Cmd& cmd : execute) {
			switch (cmd)
			{
			case Advance:avancer(30);		  break;
			case Backward:reculer(30);		  break;
			case TurnLeft45:turnLeft();	  break;
			case TurnRight45:turnRight();	  break;
			default:
				break;
			}
		}
	}

	void play2(Cmd execute) {
			switch (execute)
			{
			case Advance:avancer(30);		  break;
			case Backward:reculer(30);		  break;
			case TurnLeft45:turnLeft();	  break;
			case TurnRight45:turnRight();	  break;
			default:
				break;
			}
	}


};
