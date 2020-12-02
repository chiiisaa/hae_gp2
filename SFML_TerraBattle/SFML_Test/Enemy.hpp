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
	RectangleShape EnemyImage;
	Texture text;
	Texture textureSansFond;

	float time = 0.4;
	bool destroy = false;

	int enemyTour;

	RectangleShape healthBarBg;
	RectangleShape healthBar;
	float health = 100;
	float Maxhealth = 100;

	Enemy() {
		enemy = RectangleShape(Vector2f(64, 64));
		enemy.setOrigin(25, 25);
		EnemyImage = RectangleShape(Vector2f(64, 64));
		EnemyImage.setOrigin(25, 25);

		bool isOK = text.loadFromFile("images/cat1.png");
		textureSansFond.loadFromFile("images/cat.png");
		if (!isOK)
		{
			auto erg = 66;
		}
		enemy.setTexture(&text);
		textureSansFond.loadFromFile("images/cat.png");
		EnemyImage.setTexture(&textureSansFond);
		EnemyImage.setFillColor((sf::Color(255, 255, 255, 0)));

		this->iniHealth();
	}

	void setPosition(Vector2f pos)
	{
		enemy.setPosition(pos);

		this->healthBarBg.setPosition(enemy.getPosition());

		this->healthBar.setPosition(enemy.getPosition());
	}

	Vector2f getPosition()
	{
		return enemy.getPosition();
	}

	void Die(float dt)
	{
		time -= dt;
		//setPosition(sf::Vector2f(100 + rand() % 25, 100 + rand() % 25));
		if (time > 0.25) enemy.setRotation(rand() % 45);
		else if (time <= 0.25)
		{
			enemy.setFillColor(Color(255, 255, 255, 0));
			EnemyImage.setPosition(enemy.getPosition());
			EnemyImage.setScale(EnemyImage.getScale() + Vector2f(0.01, 0.01));
			Color c = EnemyImage.getFillColor();
			EnemyImage.setFillColor(Color(255, 255, 255, c.a -= 1));
		}
		if (time <= 0.1) destroy = true;
	}

	void Move(Vector2f target)
	{
		enemy.move(target);
	}

	bool move(Vector2f myPos, Vector2f myPosInCase, Vector2f mycase[9][6], Vector2f target, int inCase[8][6])
	{
		if (myPos == target)
		{
			return true;
			cout << "meme endroit" << endl;
		}
		float distance1 = 10000;
		Vector2f position;
		for (int x = -1; x <= 1; x++)
		{
			if (inCase[(int)myPosInCase.x - x][(int)myPosInCase.y] == 0 && x !=0)
			{
				// calcule de distance : \sqrt{ (x2 - x1)^ { 2 } + (y2 - y1)^ { 2 } }
				float distance = sqrt(pow(mycase[(int)myPosInCase.x - x][(int)myPosInCase.y].x - target.x, 2) + pow(mycase[(int)myPosInCase.x - x][(int)myPosInCase.y].y - target.y, 2));
				if (distance < distance1 && mycase[(int)myPosInCase.x - x][(int)myPosInCase.y].x > 0)
				{
					cout << mycase[(int)myPosInCase.x - x][(int)myPosInCase.y].x << endl;
					distance1 = distance;
					position = mycase[(int)myPosInCase.x - x][(int)myPosInCase.y];
				}
			}
		}
		for (int y = -1; y <= 1; y++)
		{
			if (inCase[(int)myPosInCase.x][(int)myPosInCase.y - y] == 0 && y!=0)
			{			
				float distance = sqrt(pow(mycase[(int)myPosInCase.x][(int)myPosInCase.y - y].x - target.x, 2) + pow(mycase[(int)myPosInCase.x][(int)myPosInCase.y - y].y - target.y, 2));
				if (distance < distance1 && mycase[(int)myPosInCase.x][(int)myPosInCase.y - y].y > 0)
				{
					distance1 = distance;
					position = mycase[(int)myPosInCase.x][(int)myPosInCase.y - y];
				}
			}
		}
		cout << position.x << "y : " << position.y << endl;
		setPosition(position);
		return false;
	}

	auto SearchPlayer(int inCase[8][6])
	{
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 6; x++)
			{
				//cout << inCase[y][x];
				if (inCase[y][x] == 1)
				{
					if (y != 0 && inCase[y - 1][x] != 1)
					{
						return Vector2i(y - 1, x);
					}//temporaire
					else if (x != 0 && inCase[y][x-1] != 1)
					{
						cout << x << endl;
						return Vector2i(y, x-1);
					}//temporaire
				}
			}
		}
	}

	void iniHealth() {
		this->healthBarBg.setSize(Vector2f(60, 10));
		this->healthBarBg.setFillColor(Color::Black);
		this->healthBarBg.setOrigin(Vector2f(22, -17));
		this->healthBarBg.setPosition(this->enemy.getPosition());

		this->healthBar.setSize(Vector2f(60, 10));
		this->healthBar.setFillColor(Color::Blue);
		this->healthBar.setOrigin(Vector2f(22, -17));
		this->healthBar.setPosition(this->enemy.getPosition());
	}

	void updateHp()
	{
		float percent = health / Maxhealth;
		float vie = Lerp(health, percent, 0.5);

		healthBar.setSize(Vector2f(60 * percent, healthBar.getSize().y));
	}

	void looseHp(float degat,float dt = 0)
	{
		health -= degat;

		if (health < 0)
		{
			health = 0;
			Die(dt);
		}

		updateHp();
	}

	float Lerp(float x, float y, float z) {
		return ((1.0f - z) * x) + (z * y);
	}


	void draw(sf::RenderWindow& win)
	{
		win.draw(enemy);
		win.draw(EnemyImage);

		win.draw(this->healthBarBg);
		win.draw(this->healthBar);
	}

};
