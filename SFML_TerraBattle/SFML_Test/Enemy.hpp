#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Game.hpp"
#include "player.hpp"

#include <iostream>
#include <unordered_map>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

using namespace std;
using namespace sf;

using std::size_t;
using std::hash;
using std::string;
namespace std {
	template <>
	struct hash<sf::Vector2i> {
		std::size_t operator()(const sf::Vector2i& k) const {
			return (hash<int>()(k.x) ^ (hash<int>()(k.y)) << 1);
		};
	};
}


class Enemy {
public:
	RenderWindow* win = nullptr;
	RectangleShape enemy;
	RectangleShape EnemyImage;
	Texture text;
	Texture textureSansFond;

	float time = 0.4;
	bool destroy = false;
	bool die = false;

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

	/// pas encore bon
	Vector2f LastPosEnemy;

	vector<Vector2f> Enemypos;

	vector<sf::Vector2i> allNodes;
	std::unordered_map<Vector2i, sf::Vector2i> dij_pred;
	//std::map<string, int> dij_pred;
	std::vector<float> deeeeeeeee;

	bool isFree(int a, int b, int inCase[8][6])
	{
		if (inCase[a][b] == 0)
			return true;

		return false;
	}

	void createsNodes(Vector2f myCase[9][6], int inCase[8][6], Vector2f pos) {
		allNodes.clear();
		inCase[(int)pos.x][(int)pos.y] = 0;
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 6; x++) {
				Vector2i cell(y, x);
				Vector2i s = (Vector2i)myCase[y][x];
				if (isFree(y, x, inCase))
					allNodes.push_back(cell);
			}
		}
	}

	void dij_init(std::vector<sf::Vector2i>& g, Vector2i start)
	{
		deeeeeeeee.clear();
		deeeeeeeee.resize(500000, 10000000);
		dij_pred.clear();
		for (auto& s : g) {
			int key = getKey(s);
			deeeeeeeee[key] = 1000 * 1000 * 1000;
		}
		deeeeeeeee[getKey(start)] = 0;
	}

	int getKey(sf::Vector2i vec) {
		return vec.x + (vec.y * 256);
		//x = 0 => 0
		//x =3 et y = 2
		//key = 3 + 256*2 = 511
		//=> moins de colonne que 256 
	}

	bool dij_findMin(std::vector<sf::Vector2i>& q, std::vector<float>& d, Vector2i& result) {
		float min = 1000 * 1000 * 1000;
		Vector2i vertex(-1, -1);
		bool isFound = false;
		for (auto& s : q) {
			if (d[getKey(s)] < min) {
				min = d[getKey(s)];
				vertex = s;
				isFound = true;
			}
		}
		result = vertex;
		return isFound;
	}

	static float dist(Vector2i s1, Vector2i s2) {
		return sqrt(pow(s2.x - s1.x, 2) + pow(s2.y - s1.y, 2));
	}

	void dij_update(Vector2i s1, Vector2i s2, Vector2f myCase[9][6])
	{
		int ks1 = getKey(s1);
		int ks2 = getKey(s2);
		float ndist = deeeeeeeee[ks1] + dist(Vector2i(myCase[s1.y][s1.x]), Vector2i(myCase[s2.y][s2.x]));
		//float ndist = d[ks1] + dist(s1, s2);
		if (deeeeeeeee[ks2] > ndist) {
			deeeeeeeee[ks2] = ndist;
			dij_pred[s2] = s1;
		}
	}

	vector<Vector2i> dij_getNeighbours(Vector2i elem, int inCase[8][6]) {
		vector<Vector2i> nei;

		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				if ((x == 0 && y == 0) || (x == -1 && y == -1) || (x == -1 && y == 1) || (x == 1 && y == -1) || (x == 1 && y == 1))
					continue;

				int nx = x + elem.x;
				int ny = y + elem.y;
				if (nx >= 0 && ny >= 0 && isFree(nx, ny, inCase))
					nei.push_back(Vector2i(nx, ny));
			}
		}
		return nei;
	}

	void dij_process(Vector2f myPosInCase, int inCase[8][6], Vector2f myCase[9][6]) {

		dij_init(allNodes, Vector2i((int)myPosInCase.x, (int)myPosInCase.y));
		vector<Vector2i> q = allNodes;
		while (q.size()) {
			Vector2i s1;
			bool ok = dij_findMin(q, deeeeeeeee, s1);
			auto pos = std::find(q.begin(), q.end(), s1);
			if (pos != q.end())
				q.erase(pos);

			vector<Vector2i> neighbours = dij_getNeighbours(s1, inCase);
			for (auto& s2 : neighbours)
				dij_update(s1, s2, myCase);
		}
	}

	/*void movee(Vector2f myPos, Vector2f myPosInCase, Vector2f myCase[9][6], Vector2f target, int inCase[8][6])
	{
		Vector2i sdeb = Vector2i((int)myPosInCase.x, (int)myPosInCase.y);
		Vector2i sfin = Vector2i((int)target.x, (int)target.y);

		Vector2i a = dij_pred[sdeb];
		if (sdeb == sfin)
		{
			cout << " C'est la meme !!!!" << endl;
		}
		myPosInCase = myCase[dij_pred[sdeb].x][dij_pred[sdeb].y];
		cout << " dij_pred[sdeb].x " << dij_pred[sdeb].x << "dij_pred[sdeb].y " << dij_pred[sdeb].y << endl;
		setPosition(myPosInCase);
	}*/


	bool move(Vector2f myPosInCase, Vector2f myCase[9][6], Vector2f target, int inCase[8][6])
	{
		if (myPosInCase == target)
		{
			return true;
		}
		createsNodes(myCase, inCase, myPosInCase);
		dij_process(target, inCase, myCase);
		Vector2i sdeb = Vector2i((int)myPosInCase.x, (int)myPosInCase.y);
		Vector2i sfin = Vector2i((int)target.x, (int)target.y);

		Vector2i a = dij_pred[sdeb];
		if (sdeb == sfin)
		{
			cout << " C'est la meme !!!!" << endl;
		}
		myPosInCase = myCase[dij_pred[sdeb].x][dij_pred[sdeb].y];
		setPosition(myPosInCase);
		return false;
	}


	/*auto SearchPosAttackPlayer(int inCase[8][6])
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
						targetPlayer = Vector2i(y, x);
						return Vector2i(y - 1, x);
					}//temporaire
					else if (x != 0 && inCase[y][x-1] != 1)
					{
						cout << x << endl;
						targetPlayer = Vector2i(y, x);
						return Vector2i(y, x-1);
					}//temporaire
				}
			}
		}
	}*/

	/// pas encore bon
	Vector2f p(Vector2f pos, Vector2f myCase[9][6],Vector2f StartPos, int inCase[8][6])
	{
		float tempDist = 1000 * 1000 * 1000;
		Vector2f tempCas;
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				if ((x == 0 && y == 0) || (x == -1 && y == -1) || (x == -1 && y == 1) || (x == 1 && y == -1) || (x == 1 && y == 1))
					continue;

				if (dist((Vector2i)StartPos, (Vector2i)myCase[(int)pos.x - x][(int)pos.y - y]) < tempDist && 
					isFree(pos.x - x, pos.y - y, inCase) && StartPos != myCase[(int)pos.x - x][(int)pos.y - y])
				{
					tempCas = myCase[(int)pos.x - x][(int)pos.y - y];
					tempDist = dist((Vector2i)StartPos, (Vector2i)tempCas);
				}

			}
		}
		return tempCas;
	}

	player FindPlayer(vector<player> p)
	{
		float health(200);
		player pla;
		for (player var : p)
		{
			cout << var.health << endl;
			if (var.health < health)
			{
				health = var.health;
				pla = var;
				dir = pla.getPosition() - enemy.getPosition();
			}
		}
		return pla;
	}

	float timeAttack = 0.1;
	Vector2f dir;
	bool attack(Vector2f player, float dt)
	{
		dir = dir / sqrt((dir.x * dir.x) + (dir.y * dir.y));
		cout << dir.x << " y: " << dir.y << endl;
		dir = Vector2f(dir.x * 3, dir.y * 3);
		//Longueur Vecteur |V|=racine carré de ((Vx * Vx) + (Vy * Vy))
		//normalisé Vecteur : U = V / |V |
		enemy.move(dir);
		timeAttack -= dt;
		if (timeAttack <= 0)
		{
			enemy.move(-dir);
			timeAttack = 1;
			return true;
		}
		return false;
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

	void looseHp(float degat)
	{
		health -= degat;
		if (health < 0)
		{
			die = true;
			health = 0;
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

