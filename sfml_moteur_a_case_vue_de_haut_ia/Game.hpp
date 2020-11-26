#pragma once

#include <vector>
#include <unordered_map>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "Particle.hpp"
#include "ParticleMan.hpp"
#include "Char.hpp"

using namespace sf;

class Game {
public:
	sf::RenderWindow* win = nullptr;
	sf::RectangleShape  bg;
	sf::Texture			tex;

	Char				mario;

	bool				closing = false;


	std::vector<sf::Vector2i>		walls;
	std::vector<sf::RectangleShape> wallSprites;

	ParticleMan beforeParts;
	ParticleMan afterParts;

	Game(sf::RenderWindow* win);

	void cacheWalls();

	void processInput(sf::Event ev);
	bool wasPressed = false;
	void pollInput(double dt);
	void onSpacePressed();

	void update(double dt);

	void draw(sf::RenderWindow& win);

	void onFileTick();
	bool isWall(int cx, int cy);

	void noeud();
	vector<sf::Vector2i> sommets;
	std::unordered_map<sf::Vector2i, float> d;

	void ini(Vector2i sdeb)
	{
		for (Vector2i a : sommets)
		{
			d[a] = 10000000;
		}
		d[sdeb] = 0;

	}

	//unordered_map<Vector2i, float> dis; 
};