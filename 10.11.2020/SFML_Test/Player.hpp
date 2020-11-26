#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

class Player {
public :
	static constexpr int GRID_SIZE = 16;
	RectangleShape player;

	Player()
	{
		player = RectangleShape(Vector2f(8, 32));
		player.setFillColor(sf::Color::Blue);
		player.setPosition(400, 400);
		player.setOrigin(4, 32);

	}

	Vector2f getPositionPixel() {
		return Vector2f(cx * GRID_SIZE + rx * GRID_SIZE, cy * GRID_SIZE + ry * GRID_SIZE);
	}

	void update(double dt)
	{

	}

	void draw(sf::RenderWindow& win) {
		win.draw(player);
	}

	int cx = 0;
	float rx = 0;
	
	int cy = 0;
	float ry = 0;

	void setPosition(int rpx,int rpy)
	{
		cx = rpx / GRID_SIZE;
		rx = rpx - (cx * GRID_SIZE);

		cy = rpy / GRID_SIZE;
		ry = rpy - (cy * GRID_SIZE);
	}

	void setCellPosition(int cx, int cy)
	{
		rx = 0.5;
		ry = 0.0;
		this->cx = cx;
		this->cy = cy;
	}



};
