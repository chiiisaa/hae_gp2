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

	DrawOn,
	DrawOff,
};

class tortue {
public:
	RenderWindow* win = nullptr;
	CircleShape player;

	RectangleShape a;
	Vector2f position = player.getPosition();
	Vector2f targetPosition;
	Vector2f direction;
	float angle = 0;
	float targetAngle = 0;

	float DEG_TO_RAD = 1.0 / 360 * 2 * 3.141569;

	vector<Cmd>	cmdBuffer;
	std::vector< sf::CircleShape>  steps;
	double life = 0.0;
	bool isDrawing = false;

	VertexArray line;
	std::vector<Vector2f> myPoints;

	tortue() {
		player = CircleShape(50);
		player.setFillColor(Color::Green);
		player.setOrigin(25, 25);
		player.setPosition(50, 50);
		targetPosition = player.getPosition();

		a = RectangleShape(Vector2f(60, 10));
		a.setFillColor(Color(0x50F2E4));
		a.setOrigin(0, 0);
		a.setPosition(player.getOrigin()+ Vector2f(50,50));

		line.setPrimitiveType(PrimitiveType::LineStrip);
	}

	Vector2f getPosition()
	{
		return player.getPosition();
	}

	void avancer(int val)
	{
		position = getPosition();
		direction = directionFromAngle(angle);
		direction.x *= val;
		direction.y *= val;

		position.x += direction.x;
		position.y += direction.y;

		//player.setPosition(position);
		//a.setPosition(player.getOrigin() + position);
		targetPosition = position;
		//drawLine();
	}

	void reculer(int val)
	{
		avancer(-val);
	}

	void turnLeft()
	{
		this->angle -= 45;
		a.setRotation(this->angle);
	}

	void turnRight()
	{
		this->angle += 45;
		a.setRotation(this->angle);
	}

	void turnProgressive(float angle) {
		targetAngle += angle;
		//drawLine();
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
		win.draw(line);
	}

	void update(double dt);

	void drawLine()
	{
		myPoints.push_back(player.getPosition());
		line.append(Vertex(myPoints[myPoints.size()-1], Color::Red));
	}

	void drawOn() {
		isDrawing = true;
	}


	void drawOff() {
		isDrawing = false;
	}

	void reset()
	{
		cmdBuffer.clear();
		isDrawing = false;
		targetAngle = angle = 0;
		player.setPosition(400, 400);
		targetPosition = player.getPosition();
		a.setPosition(player.getOrigin() + player.getPosition());
		a.setRotation(angle);
		steps.clear();
	}

	void setPosition(Vector2f pos)
	{
		player.setPosition(pos);
		pos.x += 32;
		pos.y += 32;
		a.setPosition(pos);
		targetPosition = pos;
	}

	void play(Cmd execute);
	void play(std::vector<Cmd> execute);
	void PlayProgressif(vector<Cmd>& execute);

	private:
		void _setPosition(sf::Vector2f pos) {
			player.setPosition(pos);
			pos.x += 32;
			pos.y += 32;
			a.setPosition(pos);
			if (isDrawing) {
				sf::CircleShape c(8);
				c.setFillColor(sf::Color(0, 255, 255));
				c.setPosition(pos);
				c.setOrigin(4, 4);
				steps.push_back(c);
			}
		}
};
