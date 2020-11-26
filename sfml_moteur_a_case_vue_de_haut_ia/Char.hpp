#pragma once

#include "SFML/Graphics.hpp"
#include<functional>
#include <iostream>


using namespace sf;

class Game;
class Char;

enum State {
	Idle,
	Running,
	Walk,
	Cover,
	Jumping,//
	WalkTo,
};


class Char {
public:
	static constexpr int GRID_SIZE = 16;

	sf::RectangleShape	spr;
	Game* game = nullptr;

	Char(Game* g = nullptr) {
		spr = RectangleShape(Vector2f(16, 64));
		spr.setFillColor(sf::Color(0xFA3092ff));
		spr.setOrigin(8, 64);
		this->game = g;
	}

	float speedX = 0.0;//rx par secondes
	float speedY = 0.0;//rx par secondes

	float maxFallSpeedY = 80.0;
	float gravityY = 4;

	State state = Idle;


	int cx = 0;
	float rx = 0.0;

	int cy = 0;
	float ry = 0.0;

	float frictX = 0.87;
	float frictY = 0.87;

	float destX = 0;
	float destY = 0;

	void setCellPosition(int cx, int cy);
	void setPosition(int rpx, int rpy);

	Vector2f getPositionPixel() {
		return Vector2f(cx * GRID_SIZE + rx * GRID_SIZE, cy * GRID_SIZE + ry * GRID_SIZE);
	}

	void update(double dt);

	void stop();

	void draw(sf::RenderWindow& win) {
		win.draw(spr);
	}

	void defaultFriction();

	void setState(State st);
	bool isWallHit(int cx, int cy);
	void onWallCollision();

	std::function<void(Char *) > updateState;
	//std::function<void(Char&)> updateState2;

	/*void doRunningState();
	void doJumpingState();*/

	static void jumping(Char*);
	static void IdleState(Char*);
	static void running(Char*);
	static void CoverState(Char*);
	static void WalkState(Char*);
	
};