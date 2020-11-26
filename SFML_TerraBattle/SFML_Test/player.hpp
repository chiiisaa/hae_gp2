#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include <iostream>

using namespace std;
using namespace sf;

class player {
public:

	RectangleShape shape;
	RectangleShape b ;

	Texture text;
	Texture textureSansFond;
	RectangleShape playerTexture;
	

	player() {
		shape = RectangleShape(Vector2f(64, 64));
		//shape.setFillColor(Color(0xEB2C4C));
		shape.setOrigin(25, 25);
		textureSansFond.loadFromFile("images/playerS.PNG");
		shape.setTexture(&textureSansFond);
		
		text.loadFromFile("images/player.PNG");
		playerTexture = RectangleShape(Vector2f(400, 350));
		playerTexture.setFillColor((sf::Color(255, 255, 255, 0)));
		playerTexture.setOrigin(25, 25);
		//playerTexture.setPosition(247, 324);
		playerTexture.setTexture(&text);

		b = RectangleShape(Vector2f(192, 64));
		b.setFillColor(Color(0x421737));
		b.setFillColor((sf::Color(255, 255, 255, 0)));
		b.setOrigin(96, 32);
		b.setPosition(Vector2f(325, 407));
		bStart();
	}

	void bStart()
	{
		b.setPosition(Vector2f(325, 407));
		b.setScale(Vector2f(5, 20));
	}

	bool bTransition()
	{
		b.setFillColor((sf::Color(255, 255, 255, 255)));
		Vector2f bScale = b.getScale();
		cout << bScale.y << endl;
		if(bScale.x <= 1) b.setScale(bScale.x, bScale.y - 0.1);
		else if (bScale.y <= 1) b.setScale(bScale.x -0.01, bScale.y);
		else b.setScale(bScale.x - 0.01 , bScale.y - 0.1);
		if (bScale.y > 1 || bScale.x > 1) return true;
		else
		{
			//bStart();
			return false;
		}

	}

	void setPosition(Vector2f pos)
	{
		shape.setPosition(pos);
	}

	void color(Color c)
	{
		shape.setFillColor(c);
	}

	Vector2f getPosition() {
		return shape.getPosition();
	}

	float mul = 0.01;
	bool Attack()
	{
		//cout << shape.getScale().x << endl;
		float size = shape.getScale().x + mul;
		if (shape.getScale().x > 2)
		{
			mul = -0.01;
		}
		shape.setScale(Vector2f(size, size));
		//cout << shape.getScale().x << endl;
		if (shape.getScale().x <= 1)
		{
			cout << "play attack false" << endl;
			mul = 0.01;
			return false;
		}
		return true;
	}

	bool playerTextureMove(int direction)
	{
		playerTexture.setFillColor((sf::Color(255, 255, 255, 255)));
		Vector2f pos = playerTexture.getPosition();
		cout << pos.y << endl;
		//playerTexture.setPosition(shape.getPosition());
		if (pos.y < 950)
		{
			playerTexture.setPosition(Vector2f(pos.x, pos.y+ direction));
			return false;
		}
		if (pos.y <= 250)
		{
			playerTexture.setPosition(Vector2f(pos.x, pos.y - direction));
		}
		return true;
	}

	int a = 6;
	void playerTextureMovee(int direction)
	{
		Vector2f pos = playerTexture.getPosition();

		switch (a)
		{
		case 6 :
			if (direction > 0) playerTexture.setPosition(Vector2f(playerTexture.getPosition().x, 950));
			a = 0;
		case 0 : 
			playerTexture.setFillColor((sf::Color(255, 255, 255, 255)));
			pos = playerTexture.getPosition();
			cout << pos.y << endl;
			playerTexture.setPosition(Vector2f(pos.x, pos.y + direction));
			if (direction > 0)
			{
				if (pos.y >= 350)
				{
					a = 1;
				}
			}
			else
			{
				if (pos.y <= 350)
				{
					a = 1;
				}
			}
			break;
		case 1:
			pos = playerTexture.getPosition();
			playerTexture.setPosition(Vector2f(pos.x, pos.y - (direction*0.5)));
			cout << pos.y << endl;
			if (direction > 0)
			{
				if (pos.y <= 200)
				{
					a = 2;
				}
			}
			else
			{
				if (pos.y >= 450)
				{
					a = 2;
				}
			}
			break;
		case 2 :
			playerTexture.setFillColor((sf::Color(255, 255, 255, 255)));
			pos = playerTexture.getPosition();
			cout << pos.y << endl;
			playerTexture.setPosition(Vector2f(pos.x, pos.y + direction ));
			/*if (pos.y < 950)
			{
				playerTexture.setPosition(Vector2f(pos.x, pos.y + direction));
			}*/
		}

		/*playerTexture.setFillColor((sf::Color(255, 255, 255, 255)));
		Vector2f pos = playerTexture.getPosition();
		cout << pos.y << endl;
		//playerTexture.setPosition(shape.getPosition());
		if (pos.y < 950)
		{
			playerTexture.setPosition(Vector2f(pos.x, pos.y + direction));
			return false;
		}
		if (pos.y <= 250)
		{
			playerTexture.setPosition(Vector2f(pos.x, pos.y - direction));
		}
		return true;*/
	}

	void limite()
	{
		if (getPosition().x > 485) setPosition(Vector2f(485, getPosition().y));
		if (getPosition().x < 84) setPosition(Vector2f(84, getPosition().y));
		if (getPosition().y > 646) setPosition(Vector2f(getPosition().x, 646));
		if (getPosition().y < 84) setPosition(Vector2f(getPosition().x, 84));
	}

	void draw(sf::RenderWindow& win)
	{
		win.draw(b);
		win.draw(shape);
		//win.draw(playerTexture);
	}
};