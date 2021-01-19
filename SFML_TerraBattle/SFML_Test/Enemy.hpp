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

	int turn;
	int debutTurn;
	CircleShape circle;
	Text textTurn;
	Font font;

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

		circle.setRadius(13);
		circle.setPosition(enemy.getPosition());

		font.loadFromFile("res/MAIAN.TTF");
		textTurn.setFont(font);
		textTurn.setString(std::to_string(turn));
		textTurn.setFillColor(Color::Black);
		textTurn.setOrigin(-7, 5);
		textTurn.setPosition(circle.getPosition());

		this->iniHealth();


	}

	void setTurn(int T)
	{
		debutTurn = T;
		turn = T;
		textTurn.setString(std::to_string(turn));
	}

	void setPosition(Vector2f pos)
	{
		enemy.setPosition(pos);

		this->healthBarBg.setPosition(enemy.getPosition());

		this->healthBar.setPosition(enemy.getPosition());
		circle.setPosition(enemy.getPosition().x + 22, enemy.getPosition().y - 35);
		textTurn.setPosition(circle.getPosition());
	}

	Vector2f getPosition()
	{
		return enemy.getPosition();
	}

	bool updateTurn()
	{
		turn -= 1;
		if (this->turn <= 0)
		{
			textTurn.setString(std::to_string(turn));
			turn = debutTurn;
			return true;
		}
		textTurn.setString(std::to_string(turn));
		return false;
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

	vector<sf::Vector2i> allNodes;
	std::unordered_map<Vector2i, sf::Vector2i> dij_pred;
	std::vector<float> d;

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
		d.clear();
		d.resize(500000, 10000000);
		dij_pred.clear();
		for (auto& s : g) {
			int key = getKey(s);
			d[key] = 1000 * 1000 * 1000;
		}
		d[getKey(start)] = 0;
	}

	int getKey(sf::Vector2i vec) {
		return vec.x + (vec.y * 256);
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
		float ndist = d[ks1] + dist(Vector2i(myCase[s1.y][s1.x]), Vector2i(myCase[s2.y][s2.x]));
		//float ndist = d[ks1] + dist(s1, s2);
		if (d[ks2] > ndist) {
			d[ks2] = ndist;
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
			bool ok = dij_findMin(q, d, s1);
			auto pos = std::find(q.begin(), q.end(), s1);
			if (pos != q.end())
				q.erase(pos);

			vector<Vector2i> neighbours = dij_getNeighbours(s1, inCase);
			if (neighbours.size() == 0) q.clear(); /// ??????
			for (auto& s2 : neighbours)
				dij_update(s1, s2, myCase);
		}
	}



	bool move(Vector2f myPosInCase, Vector2f myCase[9][6], Vector2f target, int inCase[8][6])
	{
		if (myPosInCase == target)
		{
			textTurn.setString(std::to_string(turn));
			return true;
		}
		createsNodes(myCase, inCase, myPosInCase);
		dij_process(target, inCase, myCase);
		Vector2i sdeb = Vector2i((int)myPosInCase.x, (int)myPosInCase.y);
		Vector2i sfin = Vector2i((int)target.x, (int)target.y);

		Vector2i a = dij_pred[sdeb];
		myPosInCase = myCase[dij_pred[sdeb].x][dij_pred[sdeb].y];
		setPosition(myPosInCase);
		return false;
	}


	/// temp
	Vector2f positionTarget(Vector2f pos, Vector2f myCase[9][6], Vector2f StartPos, int inCase[8][6])
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
		cout << tempCas.x << "y : " << tempCas.y << endl;
		//tempCas = StartPos;
		return tempCas;
	}

	player FindPlayer(vector<player> p)
	{
		float health(200);
		player P;
		for (player var : p)
		{
			if (var.health < health)
			{
				health = var.health;
				P = var;
				dir = P.getPosition() - enemy.getPosition();
			}
		}
		return P;
	}

	float timeAttack = 0.6;
	Vector2f dir;
	bool attack(Vector2f player, float dt, Vector2f startPos)
	{
		timeAttack -= dt;
		if (timeAttack <= 0.25)
		{
			if (timeAttack <= 0)
			{
				setPosition(startPos);
				timeAttack = 0.6;
				return true;
			}
		}
		else
		{
			Vector2f direction = Vector2f(player.x - getPosition().x, (player.y - getPosition().y));
			float norme = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			direction = direction / norme;

			enemy.move(direction);
			healthBar.move(direction);
			healthBarBg.move(direction);
			circle.move(direction);
			textTurn.move(direction);
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
		win.draw(circle);
		win.draw(textTurn);

		win.draw(this->healthBarBg);
		win.draw(this->healthBar);
	}

};

