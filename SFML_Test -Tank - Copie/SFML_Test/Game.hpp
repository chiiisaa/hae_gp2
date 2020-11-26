#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Particle.hpp"
#include "ParticleFume.h"

#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class Game {
public:
	sf::RectangleShape player;
	sf::RenderWindow* win = nullptr;
	VertexArray line;

	float MouseX;
	float MouseY;
	float speed = 10;
	Vector2f pos = player.getPosition();
	Vector2f normal;
	CircleShape tir;
	RectangleShape canon = RectangleShape(Vector2f(60, 10));
	RectangleShape bg;

	Texture text;

	vector<Particle> parts;
	vector<ParticleFume> fume;

	sf::Music music;
	sf::Music musicFond;

	Game(sf::RenderWindow* win) {
		this->win = win;
		bg = RectangleShape(Vector2f(win->getSize().x, bg.getSize().y));
		bool isOK = text.loadFromFile("images/back.jpg");
		if (!isOK)
		{
			auto erg = 66;
		}
		bg.setTexture(&text);
		bg.setSize(Vector2f(1280, 720));

		player = sf::RectangleShape(Vector2f(64, 64));
		player.setFillColor(Color(0xEB2C4C));
		player.setOutlineColor(Color(0x50F2E4));
		player.setPosition(50, 50);
		player.setOrigin(25, 25);

		canon.setFillColor(Color(0x50F2E4));

		musicFond.openFromFile("images/MUSIC_INTRO.ogg");
		musicFond.play();
	}

	void processInput(sf::Event ev) {
		if (ev.type == sf::Event::Closed)
			win->close();
		if (ev.type == sf::Event::KeyReleased) {

		}
		/*if (ev.type == Event::MouseMoved)
		{
			//Rotation du joueur 
			MouseX = ev.mouseMove.x;
			MouseY = ev.mouseMove.y;

		}*/
		
		/*if (Mouse::isButtonPressed(Mouse::Left))
		if (ev.type == Event::MouseButtonPressed)
		{
			tir = CircleShape(10);
			tir.setFillColor(Color(0x0563FA));
			tir.setPosition(pos);

			// calcul : Longueur Vecteur ||V|| =racine carré de ((Vx * Vx) + (Vy * Vy))
			// normalisé Vecteur : U = V / ||V||
			auto temp = (Vector2f(MouseX, MouseY) - pos);
			normal = temp / sqrt(pow(temp.x, 2) + pow(temp.y, 2));
		}*/
	}

	void pollInput(double dt) {
		Vector2f ppos = player.getPosition();
		pos = player.getPosition();
		float speed = 600;
		if (Keyboard::isKeyPressed(Keyboard::Key::Z))
		{
			pos.y-= dt * speed;
			particleFumee(pos);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Q))
		{
			pos.x-= dt * speed;
			particleFumee(pos);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
		{
			pos.y+= dt * speed;
			particleFumee(pos);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
		{
			pos.x += dt * speed;
			particleFumee(pos);
		}

		Vector2i mPos = sf::Mouse::getPosition(*win);
		float angle = atan2f(mPos.y - ppos.y, mPos.x - ppos.x);
		canon.setRotation((angle / (2 * 3.14156)) * 360);
		//player.setRotation((angle / (2 * 3.14156)) * 360);

		limite();

		player.setPosition(pos);
		canon.setPosition(pos);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {

			music.openFromFile("images/Sans titre.ogg");
			music.play();

			Vector2f dir(mPos.x - ppos.x, mPos.y - ppos.y);
			Vector2f pos(ppos.x, ppos.y);

			Vector2f ndir = dir;
			double len = sqrt(ndir.x * ndir.x + ndir.y * ndir.y);
			if (len <= 0.0)
				len = 1.0;
			ndir.x /= len;
			ndir.y /= len;

			pos.x += ndir.x * 48;
			pos.y += ndir.y * 48;

			spawnParticle(pos, ndir);
		}
	}

	void spawnParticle(Vector2f pos, Vector2f dir) {
		Particle p;
		p.x = pos.x;
		p.y = pos.y;

		p.dx = dir.x * 60 * 10;
		p.dy = dir.y * 60 * 10;
		parts.push_back(p);
	}

	void particleFumee(Vector2f pos)
	{
		ParticleFume p;
		p.PosX = pos.x;
		p.PosY = pos.y + 35;

		fume.push_back(p);
	}

	void limite()
	{
		if (pos.y > 680) pos.y = 680;
		if (pos.y < 29) pos.y = 29;
		if (pos.x < 30) pos.x = 30;
		if (pos.x > 1241) pos.x = 1241;
	}

	void update(double dt) {
		pollInput(dt);
		//tir.move(normal * speed);

		for (auto iter = parts.begin(); iter != parts.end(); ) {
			Particle& p = *iter;
			p.update(dt);
			if (p.destroyed)
				iter = parts.erase(iter);
			else
				iter++;
		}

		for (auto iter = fume.begin(); iter != fume.end(); ) {
			ParticleFume& p = *iter;
			p.update(dt);
			if (p.destroy)
				iter = fume.erase(iter);
			else
				iter++;
		}
	}

	void draw(sf::RenderWindow& win) {
		win.draw(bg);

		for (ParticleFume& p : fume) {
			win.draw(p.part);
		}
		win.draw(player);
		//win.draw(line);
		//win.draw(tir);
		win.draw(canon);

		for (Particle& p : parts) {
			win.draw(p.el);
		}
	}

};