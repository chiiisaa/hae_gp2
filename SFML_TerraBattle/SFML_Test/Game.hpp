#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Enemy.hpp"
#include "player.hpp"
#include "particule.hpp"
#include "Blanc.hpp"
#include "LevelManager.hpp"

#include "tuto.hpp"

#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

enum State {
	playerTurn,
	playerStartAttack,
	playerAttack,
	playerKill,

	enemyTurn,
	enemyAttack,
	enemyMove,
	enemyok,

	wait,
	Win,
	lose,
};

class Game {
public:

	LevelManager Lv;

	tuto t;

	RenderWindow* win = nullptr;

	player playercol; // sert pour pour si le player qu'on bouge n'est pas en collision avec un autre player
	player Player;

	player enemyTarget;
	vector<player> AllPlayer;
	vector<particule> partPlayer; //particule player
	Vector2f LastPlayerPos;
	Vector2f EnemyStartMovePos;

	Blanc b;

	Enemy en;
	vector<Enemy> allEnemy;
	vector<int> EnemyMove;

	RectangleShape LigneX;
	RectangleShape LigneY;

	RectangleShape bg;
	Texture text;

	float time = 5.00;
	State state;

	/// <summary>
	/// Temporaire / Teste
	/// </summary>
	Font font;
	Text stateText;
	Text tempsText;
	Text attackText;
	Text attackText1;
	vector<Text> degatText;
	vector<int> degatInt;

	RectangleShape bgNextLevel;
	Text NextText;
	Text Victoire;
	bool Nextbool;
	Text degat;

	Text winOrLose;
	Texture textCredit;
	RectangleShape end;
	Text exit;

	Music click;
	Music soundEffects;

	Vector2f myCase[9][6]{
		{Vector2f(84, 84),Vector2f(164, 84),Vector2f(247, 84),Vector2f(325, 84),Vector2f(406, 84),Vector2f(485, 84)},
		{Vector2f(84, 165),Vector2f(164, 165),Vector2f(247, 165),Vector2f(325, 165),Vector2f(406, 165),Vector2f(485, 165)},
		{Vector2f(84, 245),Vector2f(164, 245),Vector2f(247, 245),Vector2f(325, 245),Vector2f(406, 245),Vector2f(485, 245)},
		{Vector2f(84, 324),Vector2f(164, 324),Vector2f(247, 324),Vector2f(325, 324),Vector2f(406, 324),Vector2f(485, 324)},
		{Vector2f(84, 407),Vector2f(164, 407),Vector2f(247, 407),Vector2f(325, 407),Vector2f(406, 407),Vector2f(485, 407)},
		{Vector2f(84, 485),Vector2f(164, 485),Vector2f(247, 485),Vector2f(325, 485),Vector2f(406, 485),Vector2f(485, 485)},
		{Vector2f(84, 564),Vector2f(164, 564),Vector2f(247, 564),Vector2f(325, 564),Vector2f(406, 564),Vector2f(485, 564)},
		{Vector2f(84, 646),Vector2f(164, 646),Vector2f(247, 646),Vector2f(325, 646),Vector2f(406, 646),Vector2f(485, 646)},
		{Vector2f(0, 0)}
	};

	int inCase[8][6]{
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0}

	};

	Game(RenderWindow* win);

	bool mouseInPlayer = false;
	int Playeri; // index du player tableau
	void processInput(Event ev);

	//pour savoir si le player qu'on est entrain de bouger rentre en collision avec un autre joueur 
	//si oui on change la position du joueur avec lequel on est entrer en collision
	void playerCollisionWithPlayer();

	//particule Player
	void particulePlayer(Vector2f pos);

	//Cherche la valeur dans le tableau myCase et renvoie sa position dans le tableau
	Vector2f SearchValueInMyCase(Vector2f value);

	void ChangeValueInCase(Vector2f target, int value);

	//parcours le tableau MyCase et renvoie la case la plus proche du joueur
	Vector2f distanceBetweenCase(bool isPlayer = true);

	int enemyIndex;
	int playerIndex;

	//si on touche un enemy
	bool degatEnemy();

	void pollInput() {

	}

	void AttackText(Vector2f pos, Vector2f pos1);
	void AttackTextMove();

	//pour avoir l'index de l'enemie qu'il nous faut dans la list de allEnemy
	int getEnemy(Vector2f pos);
	int getPlayer(Vector2f pos);

	void update(float dt);
	void draw(RenderWindow& win);
	void setState(State st);

	void changeLevel();
	void change();

	void iniDegat(int val, int mini, int max, Vector2f pos)
	{
		degatInt.clear();
		degatText.clear();
		for (int i = 0; i < val; i++)
		{
			int randNum = rand() % (mini - max + 1) + mini;
			degatInt.push_back(randNum);
			degat.setFont(font);
			degat.setFillColor((sf::Color(255, 255, 255, 0)));
			degat.setPosition(pos);
			degat.setString(std::to_string(randNum));
			degatText.push_back(degat);
		}
	}

	float timeDegatText = 0.25;
	int i = 0;
	void EnnemyDegat(float dt)
	{
		timeDegatText -= dt;
		if (i == degatText.size())
		{
			attackText.setString(" ");
			attackText1.setString(" ");

			if (allEnemy[enemyIndex].die)
			{
				allEnemy[enemyIndex].Die(dt);
				Vector2i enemypos = (Vector2i)SearchValueInMyCase(allEnemy[enemyIndex].getPosition());
				inCase[enemypos.x][enemypos.y] = 0;
				if (allEnemy[enemyIndex].destroy)
				{
					allEnemy.erase(allEnemy.begin() + enemyIndex);
					if (allEnemy.size() <= 0)
					{
						Nextbool = true;
						//changeLevel();
						i = 0;
						setState(wait);

						if (Lv.indexLevel >= 3) setState(Win);
					}
					else
					{
						if (enemyIndex != 0) enemyIndex--; //temp
						i = 0;
						setState(enemyTurn);
					}
				}
			}
			else
			{
				i = 0;
				//AllPlayer[Playeri].reset(); AllPlayer[playerIndex].reset();
				setState(enemyTurn);
			}
		}
		else if (timeDegatText <= 0)
		{
			degatText[i].setString(" ");
			allEnemy[enemyIndex].looseHp(degatInt[i]);
			if (allEnemy[enemyIndex].die) i = degatText.size();
			else
			{
				timeDegatText = 0.25;
				i++;
			}
		}
		else {
			degatText[i].setFillColor(Color::Black);
			degatText[i].move(0, -5);
		}

	}

	void Heal()
	{

	}

	void PlayerDegat(float dt, player p)
	{
		timeDegatText -= dt;
		if (i == degatText.size())
		{
			attackText.setString(" ");
			attackText1.setString(" ");

			if (p.die)
			{
				Vector2f tempPosPlayer = p.getPosition();
				inCase[(int)SearchValueInMyCase(tempPosPlayer).x][(int)SearchValueInMyCase(tempPosPlayer).y] = 0;
				AllPlayer.erase(AllPlayer.begin() + getPlayer(tempPosPlayer));
				if (AllPlayer.size() <= 1)
				{
					//LOSE

					setState(lose);

					cout << "LOSE" << endl;
				}
				else
				{
					i = 0;
					EnemyMove.erase(EnemyMove.begin() + 0);
					if (EnemyMove.size() == 0) setState(playerTurn);
					else
					{
						//enemyIndex = EnemyMove[0];
						//EnemyStartMovePos = allEnemy[enemyIndex].getPosition();
						EnemyStartMovePos = allEnemy[EnemyMove[0]].getPosition();
						setState(enemyok);
					}
				}
			}
			else
			{
				i = 0;
				EnemyMove.erase(EnemyMove.begin() + 0);
				if (EnemyMove.size() == 0)
				{
					setState(playerTurn);
				}
				else
				{
					//EnemyStartMovePos = allEnemy[enemyIndex].getPosition();
					EnemyStartMovePos = allEnemy[EnemyMove[0]].getPosition();
					//enemyIndex = EnemyMove[0];
					setState(enemyok);
				}
			}
		}
		else if (timeDegatText <= 0)
		{
			degatText[i].setString(" ");
			AllPlayer[getPlayer(p.getPosition())].reset();
			AllPlayer[getPlayer(p.getPosition())].UpdateHp(-degatInt[i]);
			timeDegatText = 0.25;
			i++;
		}
		else {
			degatText[i].setFillColor(Color::Black);
			degatText[i].move(0, -5);
		}
	}

	void PlaysongOnce(Music& m, string s) {
		//soundEffects.openFromFile("sons/heal.ogg");
		if (m.getStatus() == sf::SoundSource::Status::Stopped)
		{
			m.openFromFile(s);
			m.play();
		}
	}
};

