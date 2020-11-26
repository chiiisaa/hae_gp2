#include "Char.hpp"
#include "Game.hpp"
#include <iostream> 

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

static int cols = 1280 / Char::GRID_SIZE;
static int lastLine = 720 / Char::GRID_SIZE - 1;

Game::Game(sf::RenderWindow* win) {
	this->win = win;
	bg = sf::RectangleShape(Vector2f(win->getSize().x, win->getSize().y));

	bool isOk = tex.loadFromFile("res/bg.jpg");
	if (!isOk) {
		printf("ERR : LOAD FAILED\n");
	}
	bg.setTexture(&tex);
	bg.setSize(sf::Vector2f(1280, 720));


	for (int i = 0; i < 1280 / Char::GRID_SIZE; ++i) {
		walls.push_back(Vector2i(i, lastLine));
	}

	for (int i = 0; i < 720 / Char::GRID_SIZE; ++i) {
		walls.push_back(Vector2i(0, i));
		walls.push_back(Vector2i((1280 / Char::GRID_SIZE) - 16 / Char::GRID_SIZE, i));
	};
	cacheWalls();
	//mario.setPosition((int)1280 * 0.5, 720);

	mario = Char(this);
	mario.setCellPosition(cols >> 1, lastLine - 1);
}

void Game::cacheWalls()
{
	wallSprites.clear();
	for (Vector2i& w : walls) {
		sf::RectangleShape rect(Vector2f(16, 16));
		rect.setPosition(w.x * Char::GRID_SIZE, w.y * Char::GRID_SIZE);
		rect.setFillColor(sf::Color(0x07ff07ff));
		wallSprites.push_back(rect);
	}
}

void Game::creatBloc(int posx, int posY) {
	walls.push_back(Vector2i(posx, posY));
	sf::RectangleShape rect(Vector2f(16, 16));
	rect.setPosition(walls[walls.size() - 1].x, walls[walls.size() - 1].y);
	rect.setFillColor(sf::Color(0x07ff07ff));
	wallSprites.push_back(rect);
}

void Game::processInput(sf::Event ev) {
	if (ev.type == sf::Event::Closed) {
		win->close();
		closing = true;
		return;
	}
	if (ev.type == Event::MouseButtonPressed)
	{
		creatBloc(ev.mouseButton.x, ev.mouseButton.y );
		cout << (ev.mouseButton.y / Char::GRID_SIZE)<< endl;
	}

	if (ev.type == sf::Event::KeyReleased) {
		/*
		if (ev.key.code == sf::Keyboard::Key::Z) {
		}

		if (ev.key.code == sf::Keyboard::Key::S) {

		}

		if (ev.key.code == sf::Keyboard::Key::Q) {
		}

		if (ev.key.code == sf::Keyboard::Key::D) {
		}
		*/

		if (ev.key.code == sf::Keyboard::Key::R) {
			mario.setCellPosition(cols >> 1, lastLine - 1);
		}

		if (ev.key.code == sf::Keyboard::Key::F) {
			//parse();
		}
		// ouvrir le descripteur de fichier
		//
		// F lire le ficher
		// lire 0 pour avancer
		// lire 1 pour reculer
		// lire 2 pour tourner a g / 3 tourner a droite
		// execute la liste de commande
		// on ferme le fichier


	}
}

void Game::draw(sf::RenderWindow& win) {
	if (closing) return;

	win.draw(bg);

	beforeParts.draw(win);

	for (sf::RectangleShape& r : wallSprites)
		win.draw(r);
	//turtle.draw(win);
	mario.draw(win);

	afterParts.draw(win);
}

void Game::pollInput(double dt) {

	float lateralSpeed = 8.0;
	float maxSpeed = 40.0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		mario.speedX -= lateralSpeed;
		if (mario.speedX < -maxSpeed)
			mario.speedX = -maxSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		mario.speedX += lateralSpeed;
		if (mario.speedX > maxSpeed)
			mario.speedX = maxSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {
		mario.state = Jumping;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		if (mario.state != Jumping)
		{
			mario.speedY = -100;
			mario.state = Jumping;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		if (!wasPressed) {
			onSpacePressed();
			wasPressed = true;
		}
	}
	else {
		wasPressed = false;
	}

}

void Game::onSpacePressed() {

}

void Game::onFileTick() {

}

bool Game::isWall(int cx, int cy)
{
	for (Vector2i& w : walls) {
		if (w.x == cx && w.y == cy)
			return true;
	}
	return false;
}

static float timer = 0.0;
void Game::update(double dt) {
	pollInput(dt);

	beforeParts.update(dt);

	mario.update(dt);

	afterParts.update(dt);

	timer -= dt;
	if (timer <= 0.0) {
		onFileTick();
		timer = 0.1;
	}
}
