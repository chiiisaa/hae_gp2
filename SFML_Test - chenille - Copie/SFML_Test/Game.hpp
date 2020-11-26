#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "totue.hpp"

#include <iostream>


using namespace std;
using namespace sf;

class Game {
public:
	sf::RenderWindow* win = nullptr;
	tortue Tortue;
	tortue posTemp;
	FILE *file;

	Game(sf::RenderWindow* win) {
		this->win = win;

	}

	void processInput(sf::Event ev) {
		if (ev.type == sf::Event::Closed)
			win->close();

		if (ev.type == sf::Event::KeyReleased) {
			if (ev.key.code == sf::Keyboard::Key::Z)
				Tortue.avancer(30);

			if (ev.key.code == sf::Keyboard::Key::S)
				Tortue.reculer(30);

			if (ev.key.code == sf::Keyboard::Key::Q)
				Tortue.turnProgressive(-45);

			if (ev.key.code == sf::Keyboard::Key::D)
				Tortue.turnProgressive(45);

			if (ev.key.code == sf::Keyboard::Key::R) {
				Tortue.reset();
			}

			if (ev.key.code == sf::Keyboard::Key::T) {
				vector<Cmd> cmds = { Cmd::Advance, Cmd::Advance, Cmd::Advance, Cmd::Advance,Cmd::TurnLeft45, Cmd::Advance };
				Tortue.reset();
				Tortue.play(cmds);
			}
			if (ev.key.code == Keyboard::Key::F)
			{
				parse();
			}
		}
	}

	void pollInput(double dt) {
	}

	void draw(sf::RenderWindow& win) {
		Tortue.draw(win);
	}

	void parse()
	{
		file = fopen("test.txt", "r");
		if (file != NULL)
		{
			vector<Cmd> cmds;
			int retVal = 0;
			do {
				char _cmd[128] = {};
				retVal = fscanf(file, "%s", _cmd);
				string strCmd(_cmd);
				printf("curCnd: %s\n", _cmd);
				if (strCmd == "Advance") cmds.push_back(Advance);
				else if (strCmd == "Backward") cmds.push_back(Backward);
				else if (strCmd == "TurnLeft") cmds.push_back(TurnLeft45);
				else if (strCmd == "TurnRight") cmds.push_back(TurnRight45);
				else if (strCmd == "DrawOn") cmds.push_back(DrawOn);
				else if (strCmd == "DrawOff") cmds.push_back(DrawOff);
			} while (retVal != EOF);

			Tortue.reset();
			Tortue.PlayProgressif(cmds);
		}
		else
		{
			cout << "erroorr" << endl;
		}
		fclose(file);
	}

	void onFileTick();
	void update(double dt);
};
