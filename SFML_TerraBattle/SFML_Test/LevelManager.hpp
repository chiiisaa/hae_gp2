#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

#include <fstream>
#include <sstream>

#include <unordered_map>

using namespace sf;
using namespace std;

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


class LevelManager
{
public:
	std::string line;
	std::string introText;
	unordered_map<string, int> numbreOfCharacter;

	unordered_map<int, Vector2i> PositionE;
	unordered_map<int, int> EnemyTurn;

	unordered_map<int, Vector2i> PositionPerso;
	unordered_map<int, Vector2i> PersoHealer;
	unordered_map<int, Vector2i> PositionHealer;

	RectangleShape bg;
	Font font;
	Text text;

	int indexLevel = 0;

	LevelManager()
	{
		bg = RectangleShape(Vector2f(640, 960));

		if (!font.loadFromFile("res/MAIAN.TTF"))
		{

		}
		text.setFont(font);
		text.setFillColor(Color::Red);
		text.setOutlineThickness(0.5);
		text.setOutlineColor(Color::Black);
		text.setString("Next Level");
	}

	void nextLevel()
	{
		numbreOfCharacter.clear();
		PositionPerso.clear();
		PositionE.clear();
		indexLevel++;
		loadLevel(indexLevel);
		cout << indexLevel << endl;
	}

	void loadLevel(int levelIndex)
	{
		switch (levelIndex)
		{
		case 0:
			numbreOfCharacter["Personage"] = 2;
			numbreOfCharacter["Healer"] = 1;
			numbreOfCharacter["Enemy"] = 1;
			PositionPerso[0] = Vector2i(1, 1);
			PositionPerso[1] = Vector2i(4, 1);
			PositionE[0] = Vector2i(2, 5);
			PositionHealer[0] = Vector2i(3, 4);
			break;
		case 1:
			numbreOfCharacter["Personage"] = 3;
			numbreOfCharacter["Enemy"] = 2;
			PositionPerso[0] = Vector2i(2, 2);
			PositionPerso[1] = Vector2i(4, 1);
			PositionPerso[2] = Vector2i(4, 5);
			PositionE[0] = Vector2i(2, 5);
			PositionE[1] = Vector2i(3, 2);
			break;
		case 2:
			numbreOfCharacter["Personage"] = 3;
			numbreOfCharacter["Enemy"] = 3;
			PositionPerso[0] = Vector2i(1, 1);
			PositionPerso[1] = Vector2i(4, 1);
			PositionPerso[2] = Vector2i(3, 4);
			PositionE[0] = Vector2i(2, 5);
			PositionE[1] = Vector2i(3, 2);
			PositionE[2] = Vector2i(5, 5);
			break;
		case 3:
			numbreOfCharacter["Personage"] = 2;
			numbreOfCharacter["Healer"] = 1;
			numbreOfCharacter["Enemy"] = 3;
			EnemyTurn[0] = 3;
			EnemyTurn[1] = 2;
			EnemyTurn[2] = 1;
			PositionPerso[0] = Vector2i(1, 1);
			PositionPerso[1] = Vector2i(4, 1);
			PositionE[0] = Vector2i(2, 5);
			PositionE[1] = Vector2i(3, 2);
			PositionE[2] = Vector2i(5, 5);
			PositionHealer[0] = Vector2i(3, 4);
			break;
		default:
			break;
		}
	}

	void draw(sf::RenderWindow& win)
	{
		win.draw(bg);
		win.draw(text);
	}
};