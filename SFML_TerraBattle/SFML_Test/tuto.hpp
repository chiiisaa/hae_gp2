#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

#include <fstream>
#include <sstream>

#include <unordered_map>
#include <SFML/Audio.hpp>
#include "GState.h"

using namespace sf;
using namespace std;

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

class tuto
{
public:

	std::string line;
	std::string introText;

	unordered_map<string, string> Face;
	Texture texturePerso;
	Texture textureBg;
	Texture texturePlayer;
	Texture textureEnemie;

	unordered_map<string, string> Audio;
	Music sound;

	Font font;
	Text text;

	vector<RectangleShape> player;
	vector<RectangleShape> enemie;

	bool _next = false;
	int Progress = 0;

	RectangleShape shape;
	RectangleShape bg;
	RectangleShape LigneX;
	RectangleShape LigneY;

	tuto()
	{
		shape = RectangleShape(Vector2f(100, 100));
		shape.setOrigin(25, 25);
		texturePerso.loadFromFile("images/Sleep.png");
		shape.setTexture(&texturePerso);
		setposition(94, 94);

		bg = RectangleShape(Vector2f(640, 960));
		textureBg.loadFromFile("images/bg.jpg");
		bg.setTexture(&textureBg);

		texturePlayer.loadFromFile("images/playerS.PNG");
		textureEnemie.loadFromFile("images/cat1.png");

		LigneX = RectangleShape(Vector2f(5, 640));
		LigneX.setOrigin(0, 0);
		LigneX.setFillColor(Color::White);
		LigneY = RectangleShape(Vector2f(480, 5));
		LigneY.setOrigin(0, 0);
		LigneY.setFillColor(Color::White);

		font.loadFromFile("res/MAIAN.TTF");
		text.setFont(font);
		text.setFillColor(Color::Red);
		text.setString("ZZZZ");

		Face["happy"] = "images/happy.PNG";
		Face["sad"] = "images/sad.PNG";
		Face["combat"] = "images/combat.png";
		Audio["hey"] = "sons/hey.ogg";
	}

	void pollInput() {

	}

	void update()
	{

	}

	void draw(sf::RenderWindow& win)
	{
		win.draw(bg);
		int tempX = 50;
		for (int y = 0; y < 9; y++)
		{
			LigneY.setPosition(50, tempX);
			win.draw(LigneY);
			tempX += 80;
		}
		tempX = 50;
		for (int x = 0; x < 7; x++)
		{
			LigneX.setPosition(tempX, 50);
			win.draw(LigneX);
			tempX += 80;
		}
		for (RectangleShape r : player)
		{
			win.draw(r);
		}
		for (RectangleShape r : enemie)
		{
			win.draw(r);
		}

		win.draw(shape);
		win.draw(text);
	}

	void processInput(Event ev,GameSate& GS) {

		if (ev.key.code == Keyboard::Key::H)
		{

		}
		if (ev.type == Event::MouseButtonPressed) {
			Line(Progress,GS);
			Progress++;
		}
	}

	void Line(int levelIndex, GameSate& GS)
	{
		FILE* Level = fopen("res/tuto.txt", "r");
		std::ifstream file("res/tuto.txt"); ;

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

				for (int i = 0; i <= levelIndex; i++)
				{
					std::getline(file, line);
				}
				dialogueAndActions(line,GS);
				//s(line, '"', '"');
				break;
			} while (retVal != EOF);
		}
	}

	void dialogueAndActions(string& y, GameSate& GS)
	{
		string& t = y;
		string texte = s(y, '"', '"');
		text.setString(texte);
		text.setScale(0.5, 0.5);
		t.erase(0, texte.length());
		vector<string>Actions = se(t, '/', '/');
		aaa(Actions, GS);
		//HandleAction(Actions);
	}

	void aaa(vector<string>Actions, GameSate& GS)
	{
		for (int i = 0; i < Actions.size(); i++)
		{
			if (containe(Actions[i], "setPosition"))
			{
				string data = s(Actions[i], '(', ')');
				CommandSetPosition(data);
				cout << "position" << endl;
			}
			else if (containe(Actions[i], "setFace"))
			{
				string data = s(Actions[i], '(', ')');
				CommandSetFace(data);
				cout << "face" << endl;
			}
			else if (containe(Actions[i], "playSound"))
			{
				string data = s(Actions[i], '(', ')');
				CommandPlaySound(data);
				cout << "playSound" << endl;
			}
			else if (containe(Actions[i], "setPlayer"))
			{
				string data = s(Actions[i], '(', ')');
				CommandSetPlayer(data);
			}
			else if (containe(Actions[i], "setEnemi"))
			{
				string data = s(Actions[i], '(', ')');
				CommandSetEnemie(data);
			}
			else if (containe(Actions[i], "End"))
			{
				GS = GamePlayState;
			}
		}
	}

	void CommandPlaySound(string data)
	{
		sound.openFromFile(Audio[data]);
		sound.play();
	}

	void CommandSetPosition(string data)
	{
		vector<string> param = coup(data, ',');
		std::string::size_type sz;
		int param1 = std::stoi(param[0], &sz);
		int param2 = std::stoi(param[1], &sz);
		cout << "param1:  " << param1 << endl;
		setposition(param1, param2);
	}

	void CommandSetPlayer(string data)
	{
		player.clear();
		RectangleShape temp = RectangleShape(Vector2f(64, 64));
		temp.setOrigin(25, 25);
		temp.setTexture(&texturePlayer);
		int x = 1;
		int y = 2;
		vector<string> param = coup(data, ',');
		std::string::size_type sz;
		int numbre = std::stoi(param[0], &sz);
		for (int i = 0; i < numbre; i++)
		{
			int positionX = std::stoi(param[x], &sz);
			int positionY = std::stoi(param[y], &sz);
			player.push_back(temp);
			player[i].setPosition(positionX, positionY);
			x += 2;
			y += 2;
		}
	}

	void CommandSetEnemie(string data)
	{
		enemie.clear();
		RectangleShape temp = RectangleShape(Vector2f(64, 64));
		temp.setOrigin(25, 25);
		temp.setTexture(&textureEnemie);
		int x = 1;
		int y = 2;
		vector<string> param = coup(data, ',');
		std::string::size_type sz;
		int numbre = std::stoi(param[0], &sz);
		for (int i = 0; i < numbre; i++)
		{
			int positionX = std::stoi(param[x], &sz);
			int positionY = std::stoi(param[y], &sz);
			enemie.push_back(temp);
			enemie[i].setPosition(positionX, positionY);
			x += 2;
			y += 2;
		}
	}

	void setposition(int a, int b)
	{
		shape.setPosition(a, b);
		text.setPosition(shape.getPosition().x, shape.getPosition().y - 50);
	}

	void CommandSetFace(string data)
	{
		texturePerso.loadFromFile(Face[data]);
		shape.setTexture(&texturePerso);
	}

	vector<string> coup(string& s, char ch)
	{
		vector<string> final;
		string temp;

		for (int i = 0; i <= s.length(); i++)
		{
			char& c = s[i];
			temp += s[i];
			if (i == s.length())
			{
				final.push_back(temp);
				continue;
			}
			if (c == ch)
			{
				temp.erase(temp.length() - 1, temp.length());
				//cout << temp << endl;
				final.push_back(temp);
				temp.clear();
			}
		}
		return final;
	}

	vector<string> se(string& s, char char1, char char2)
	{
		int a = 0;
		string temp;
		vector<string> tem;


		int indexA = 0;
		int d = 1;
		for (int i = 0; i < s.length(); i++)
		{
			char& c = s[i];
			temp += s[i];

			if (c == char1 && a == indexA)
			{
				a++;
				indexA += 2; // 0 2 4 6 8 10
				temp.clear();
				//continue;
			}
			else if (c == char2 && a == d)
			{
				d += 2; // 1 3 5 7 9 11
				a++;
				temp.erase(temp.length() - 1, temp.length());
				tem.push_back(temp);
			}
		}
		return tem;
	}

	string s(string& s, char char1, char char2)
	{
		int a = 0;
		string temp;

		for (int i = 0; i < s.length(); i++)
		{
			char& c = s[i];
			temp += s[i];
			if (c == char1 && a == 0)
			{
				a++;
				temp.clear();
			}
			else if (c == char2 && a == 1)
			{
				temp.erase(temp.length() - 1, temp.length());
				cout << temp << endl;
				return temp;
			}
		}
		return "";
	}

	bool containe(string& s, string text)
	{
		string temp;

		for (int i = 0; i < s.length(); i++)
		{
			temp += s[i];
			if (temp == text)
			{
				return true;
			}
		}
		return false;
	}
};