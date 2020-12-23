#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "AssetManager.hpp"
using namespace sf;

#define MAX_Number 2

class MainMenu
{
public:
	int index;
	Font font;
	Text text[MAX_Number];
	RenderWindow* win = nullptr;
	bool Start;
	RectangleShape bg;
	AssetManager as;

	MainMenu(RenderWindow* win, float widht, float h)
	{
		this->win = win;

		bg = RectangleShape(Vector2f(widht, h));
		as.LoadTexture("bg1","images/bg1.jpg");
		bg.setTexture(&as.GetTexture("bg1"));

		if (!font.loadFromFile("res/MAIAN.TTF"))
		{

		}
		text[0].setFont(font);
		text[0].setFillColor(Color::Red);
		text[0].setOutlineThickness(0.5);
		text[0].setOutlineColor(Color::Black);
		text[0].setString("Play");
		//text[0].setOrigin(0, 0);
		text[0].setPosition(Vector2f(widht / 2, h / (MAX_Number + 1) * 1));
		
		text[1].setFont(font);
		text[1].setFillColor(Color::White);
		text[1].setOutlineThickness(0.5);
		text[1].setOutlineColor(Color::Black);
		text[1].setString("Exit");
		//text[0].setOrigin(0, 0);
		text[1].setPosition(Vector2f(widht / 2, h / (MAX_Number + 1) * 2));

		index = -1;
		
		Start = false;

	}

	~MainMenu()
	{
		
	}

	Vector2f bouton(Vector2f pos)
	{
		return Vector2f(pos.x + 20, pos.y + 20);
	}

	void update()
	{

	}

	void processInput(Event ev,GameSate& GS)
	{
		if (ev.type == Event::MouseMoved)
		{
			for (int i =0 ; i < MAX_Number; i++)
			{
				/*cout << var.getPosition().y << endl;
				cout << "mouse :  " <<  ev.mouseMove.y << endl;*/
				if (ev.mouseMove.x > text[i].getPosition().x - 20 && ev.mouseMove.x < text[i].getPosition().x + 40
					&& ev.mouseMove.y > text[i].getPosition().y - 20 && ev.mouseMove.y < text[i].getPosition().y +40)
				{
					index = i;
					text[i].setFillColor(Color::Red);
					break;
				}
				else
				{
					index = -1;
					text[i].setFillColor(Color::White);
				}
			}
		}

		if (ev.type == Event::MouseButtonReleased)
		{
			switch (index)
			{
			case 0:
				cout << "click" << endl;
				GS = GamePlayState;
				Start = true;
				break;

			case 1:
				win->close();
				break;

			default:
				cout << " no" << endl;
				break;
			}
		}
	}


	void draw(sf::RenderWindow& win)
	{
		win.draw(bg);
		for (int i = 0; i < MAX_Number; i++)
		{
			win.draw(text[i]);
		}
	}
};


