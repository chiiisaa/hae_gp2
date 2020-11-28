#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Game.hpp"

#include <iostream>

using namespace std;
using namespace sf;


class Enemy {
public:
	RenderWindow* win = nullptr;
	RectangleShape enemy;
	RectangleShape EnImage;
	Texture text;
	Texture textureSansFond;

	float time = 0.4;
	bool destroy = false;

	int enemyTour;
	
	Enemy() {
		enemy = RectangleShape(Vector2f(64, 64));
		enemy.setOrigin(25, 25);
		EnImage = RectangleShape(Vector2f(64, 64));
		EnImage.setOrigin(25, 25);

		bool isOK = text.loadFromFile("images/cat1.png");
		textureSansFond.loadFromFile("images/cat.png");
		if (!isOK)
		{
			auto erg = 66;
		}
		enemy.setTexture(&text);
		textureSansFond.loadFromFile("images/cat.png");
		EnImage.setTexture(&textureSansFond);
		EnImage.setFillColor((sf::Color(255, 255, 255, 0)));
	}

	void setPosition(Vector2f pos)
	{
		enemy.setPosition(pos);
	}

	Vector2f getPosition()
	{
		return enemy.getPosition();
	}

	void scale()
	{
		enemy.setScale(enemy.getScale() + Vector2f(0.5, 0.5));
	}

	void Die(float dt)
	{
		time -= dt;
		//setPosition(sf::Vector2f(100 + rand() % 25, 100 + rand() % 25));
		if (time > 0.25) enemy.setRotation(rand() % 45);
		else if (time <= 0.25)
		{
			enemy.setFillColor(Color(255, 255, 255, 0));
			EnImage.setPosition(enemy.getPosition());
			EnImage.setScale(EnImage.getScale() + Vector2f(0.01, 0.01));
			Color c = EnImage.getFillColor() ;
			EnImage.setFillColor(Color(255, 255, 255, c.a-=1));
			//cout << (int)c.a << endl;
		}
		if (time <= 0.1) destroy = true;
		//cout << time << endl;
	}

	void Move(Vector2f target)
	{
		enemy.move(target);
	}

	bool move(Vector2f myPos, Vector2f myPosInCase,Vector2f mycase[9][6], Vector2f target)
	{
		if (myPos == target) // teste 
		{
			return true;
			cout << "meme endroit" << endl;
		}
		float distance1 = 10000;
		Vector2f position;
		for (int x = -1; x <= 1; x++)
		{
			// calcule de distance : \sqrt{ (x2 - x1)^ { 2 } + (y2 - y1)^ { 2 } }
			float distance = sqrt(pow(mycase[(int)myPosInCase.x - x][(int)myPosInCase.y].x - target.x, 2) + pow(mycase[(int)myPosInCase.x - x][(int)myPosInCase.y].y - target.y, 2));
			if (distance < distance1)
			{
				distance1 = distance;
				position = mycase[(int)myPosInCase.x - x][(int)myPosInCase.y];
			}
			
		}
		for (int y = -1; y <= 1; y++)
		{
			float distance = sqrt(pow(mycase[(int)myPosInCase.x][(int)myPosInCase.y - y].x - target.x, 2) + pow(mycase[(int)myPosInCase.x][(int)myPosInCase.y - y].y - target.y, 2));
			if (distance < distance1)
			{
				distance1 = distance;
				position = mycase[(int)myPosInCase.x][(int)myPosInCase.y - y];
			}
		}
		setPosition(position);
		return false;
	}


	void draw(sf::RenderWindow& win)
	{
		win.draw(enemy);
		win.draw(EnImage);
	}

};
