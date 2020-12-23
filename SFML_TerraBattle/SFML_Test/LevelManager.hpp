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
	unordered_map<string, int> Perso;
	unordered_map<int, Vector2i> PositionPerso;
	unordered_map<int, Vector2i> PositionE;

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
		/*if (ev.type == Event::MouseButtonReleased && 
			ev.mouseMove.x > text.getPosition().x - 20 && ev.mouseMove.x < text.getPosition().x + 40
			&& ev.mouseMove.y > text.getPosition().y - 20 && ev.mouseMove.y < text.getPosition().y + 40)
		{

			Perso.clear();
			PositionPerso.clear();
			indexLevel++;
			loadLevelFile(indexLevel);
			cout << "Load" << endl;
		}*/

		Perso.clear();
		PositionPerso.clear();
		PositionE.clear();
		indexLevel++;
		//loadLevelFile(indexLevel);
		loadLevel(indexLevel);
		cout << indexLevel << endl;
	}

	void loadLevel(int levelIndex)
	{
		switch (levelIndex)
		{
		case 0:
			Perso["Personage"] = 2;
			Perso["Enemy"] = 2;
			PositionPerso[0] = Vector2i(1, 1);
			PositionPerso[1] = Vector2i(5, 1);
			PositionE[0] = Vector2i(2, 2);
			PositionE[1] = Vector2i(3, 2);
			break;
		case 1:
			Perso["Personage"] = 3;
			Perso["Enemy"] = 2;
			PositionPerso[0] = Vector2i(2, 2);
			PositionPerso[1] = Vector2i(4, 1);
			PositionPerso[2] = Vector2i(4, 5);
			PositionE[0] = Vector2i(2, 5);
			PositionE[1] = Vector2i(3, 2);
			break;
		case 2:
			Perso["Personage"] = 3;
			Perso["Enemy"] = 3;
			PositionPerso[0] = Vector2i(1, 1);
			PositionPerso[1] = Vector2i(4, 1);
			PositionPerso[2] = Vector2i(3, 4);
			PositionE[0] = Vector2i(2, 5);
			PositionE[1] = Vector2i(3, 2);
			PositionE[2] = Vector2i(5, 5);
			break;
		default:
			break;
		}
	}

	void loadLevelFile(int levelIndex)
	{
		FILE* Level = fopen("res/level.txt", "r");
		std::ifstream file("res/level.txt"); ;
		
		if (!Level) {
			printf("no such file res/cmd.txt\n");
		}
		else
		{
			int retVal = 0;
			do {
				char _cmd[128] = {};
				retVal = fscanf(Level, "%s", _cmd);
				string strCmd(_cmd);

				if (strCmd == std::to_string(levelIndex))
				{
					for (int i = 0; i <= levelIndex; i++)
					{
						std::getline(file, line);
					}
					split(line);
					break;
				}
			} while (retVal != EOF);
		}
	}

	void split(string& s)
	{
		string temp;

		for (int i = 0; i < s.length(); i++)
		{
			char& c = s[i];
			//cout << c << endl;
			temp += s[i];
			if (temp == "Position")
			{
				s.erase(0, i + 1);
				temp.clear();
				break;
			}
			if (c == ' ')
			{
				temp.clear();
				//f.erase(0, i+1);
			}
			if (c == ':')
			{
				temp.erase(temp.length() - 1, temp.length());
				//f.erase(0, i+1);
				//f.erase(0+1, f.length()-1);
				Perso[temp] = s[i+1] - 48;
			}
		}

		for (int i = 0; i < s.length(); i++)
		{
			char& c = s[i];
			temp += s[i];
			if (temp == "PositionE")
			{
				s.erase(0, i + 1);
				temp.clear();
				break;
			}
			if (c == ' ')
			{
				temp.clear();
				//f.erase(0, i+1);
			}
			if (c == ':')
			{
				Vector2i t = Vector2i(s[i + 1] - 48, s[i + 3] - 48);
				PositionPerso[s[i - 1] - 48] = t;
			}
		}

		for (int i = 0; i < s.length(); i++)
		{
			char& c = s[i];
			temp += s[i];
			if (c == ' ')
			{
				temp.clear();
				//f.erase(0, i+1);
			}
			if (c == ':')
			{
				Vector2i t = Vector2i(s[i + 1] - 48, s[i + 3] - 48);
				PositionE[s[i - 1] - 48] = t;
			}
		}
	}

	void draw(sf::RenderWindow& win)
	{
		win.draw(bg);
		win.draw(text);
	}
};