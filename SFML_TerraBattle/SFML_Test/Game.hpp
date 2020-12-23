#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Enemy.hpp"
#include "player.hpp"
#include "particule.hpp"
#include "Blanc.hpp"
#include "LevelManager.hpp"

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

	win,
	loose,
};

enum GameSate { Menu, GamePlayState, LevelState};

class Game {
public :

	LevelManager Lv;

	RenderWindow* win = nullptr;
	//RectangleShape player;
	//RectangleShape player2;

	player playercol; // sert pour pour si le player qu'on bouge n'est pas en collision avec un autre player
	player Player;
	vector<player> AllPlayer;
	Vector2f LastPlayerPos; 
	vector<particule> partPlayer; //particule player

	Blanc b;

	Enemy en;
	vector<Enemy> allEnemy;

	RectangleShape LigneX;
	RectangleShape LigneY;

	RectangleShape bg;
	Texture text;

	float time = 5.00;
	State state = playerTurn;

	/// <summary>
	/// Temporaire
	/// </summary>
	Font font;
	Text stateString;
	Text tempsText;

	RectangleShape bgNextLevel;
	Text NextText;
	Text Victoire;
	bool Nextbool;
	Text degat;

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

	void ChangeValueInCase(Vector2f target,int value);

	//parcours le tableau MyCase et renvoie la case la plus proche du joueur
	Vector2f distanceBetweenCase(bool isPlayer = true);

	int enemyIndex;
	int playerIndex;

	//si on touche un enemy
	bool degatEnemy();

	void pollInput() {

	}

	//pour avoir l'index de l'enemie qu'il nous faut dans la list de allEnemy
	int getEnemy(Vector2f pos);

	int getPlayer(Vector2f pos);

	void update(float dt);

	void draw(RenderWindow& win);

	void setState(State st);

	void changeLevel();
	void change();
};
