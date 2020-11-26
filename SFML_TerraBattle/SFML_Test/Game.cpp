#include "Game.hpp"

Game::Game(RenderWindow* win)
{
	this->win = win;
	bg = RectangleShape(Vector2f(win->getSize().x, bg.getSize().y));
	bool isOK = text.loadFromFile("images/bg.jpg");
	if (!isOK)
	{
		auto erg = 66;
	}
	bg.setTexture(&text);
	bg.setSize(Vector2f(640, 960));

	Player.setPosition(myCase[1][1]);
	/*player = RectangleShape(Vector2f(64, 64));
	player.setFillColor(Color(0xEB2C4C));
	player.setOrigin(25, 25);
	player.setPosition(50, 50);*/
	AllPlayer.push_back(Player);

	/*player2 = RectangleShape(Vector2f(64, 64));
	player2.setFillColor(Color(0xEB2C4C));
	player2.setOrigin(25, 25);
	player2.setPosition(myCase[5][5]);*/

	//AllPlayer.push_back(Player);

	Player.setPosition(myCase[5][5]);
	AllPlayer.push_back(Player);

	Player.setPosition(myCase[6][5]);
	AllPlayer.push_back(Player);

	//player3.insert(player3.begin() + 5, player);

	LigneX = RectangleShape(Vector2f(5, 640));
	LigneX.setOrigin(0, 0);
	LigneX.setFillColor(Color::White);
	LigneY = RectangleShape(Vector2f(480, 5));
	LigneY.setOrigin(0, 0);
	LigneY.setFillColor(Color::White);

	/*enemy = RectangleShape(Vector2f(64, 64));
	enemy.setFillColor(Color::Red);
	enemy.setOrigin(25, 25);
	enemy.setPosition(myCase[5][4]);*/
	en.setPosition(myCase[5][4]);
	allEnemy.push_back(en);
	en.setPosition(myCase[2][2]);
	allEnemy.push_back(en);
	inCase[5][4] = -1;
	inCase[2][2] = -1;
	inCase[5][5] = 1;
	inCase[1][1] = 1;
	inCase[6][5] = 1;

	state = playerTurn;
}

// index du player tableau
void Game::processInput(Event ev)
{
	if (ev.type == Event::Closed)
		win->close();

	if (ev.key.code == Keyboard::Key::P)
	{
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 6; x++)
			{
				cout << inCase[y][x];
			}
			cout << endl;
		}
	}

	if (ev.type == Event::MouseButtonPressed && state == playerTurn)
	{
		for (int i = 0; i < AllPlayer.size(); i++)
		{
			Vector2f mouseHitPlayer = AllPlayer[i].getPosition();
			if (ev.mouseButton.x > mouseHitPlayer.x - 32 && ev.mouseButton.x < mouseHitPlayer.x + 32 && ev.mouseButton.y > mouseHitPlayer.y - 32 && ev.mouseButton.y < mouseHitPlayer.y + 32)
			{
				playercol.setPosition(AllPlayer[i].getPosition());
				inCase[(int)SearchValueInMyCase(AllPlayer[i].getPosition()).x][(int)SearchValueInMyCase(AllPlayer[i].getPosition()).y] = 0;
				Playeri = i;
				mouseInPlayer = true;
			}
		}
	}

	if (ev.type == Event::MouseMoved)
	{
		if (mouseInPlayer) {
			AllPlayer[Playeri].setPosition(Vector2f(ev.mouseMove.x, ev.mouseMove.y));
			AllPlayer[Playeri].limite();
			playerCollisionWithPlayer();
			particulePlayer(distanceBetweenCase(false));
			particulePlayer(Vector2f(ev.mouseMove.x, ev.mouseMove.y));
		}
	}

	if (ev.type == Event::MouseButtonReleased && mouseInPlayer)
	{
		AllPlayer[Playeri].setPosition(distanceBetweenCase());
		enemydie = degatEnemy();
		mouseInPlayer = false;
	}
}

//pour savoir si le player qu'on est entrain de bouger rentre en collision avec un autre joueur 
//si oui on change la position du joueur avec lequel on est entrer en collision
void Game::playerCollisionWithPlayer()
{
	playercol.setPosition(distanceBetweenCase(false));
	for (player& p : AllPlayer)
	{
		if (&p != &AllPlayer[Playeri] && playercol.getPosition() == p.getPosition())
		{
			Vector2f casetemp = SearchValueInMyCase(Vector2f(p.getPosition().x, p.getPosition().y));
			inCase[(int)casetemp.x][(int)casetemp.y] = 0;
			p.setPosition(LastPlayerPos);
			casetemp = SearchValueInMyCase(Vector2f(p.getPosition().x, p.getPosition().y));
			inCase[(int)casetemp.x][(int)casetemp.y] = 1;
			//cout << "x " << p.getPosition().x << "Y : " << p.getPosition().y << endl;
			break;
		}
	}
	Vector2f casetemp = SearchValueInMyCase(Vector2f(playercol.getPosition().x, playercol.getPosition().y));
	if (inCase[(int)casetemp.x][(int)casetemp.y] != -1) LastPlayerPos = playercol.getPosition();
}

//particule Player
void Game::particulePlayer(Vector2f pos)
{
	particule p;
	p.PosX = pos.x;
	p.Posy = pos.y;

	partPlayer.push_back(p);
}

//Cherche la valeur dans le tableau myCase et renvoie sa position dans le tableau
Vector2f Game::SearchValueInMyCase(Vector2f value)
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 6; x++)
		{
			if (myCase[y][x] == value)
			{
				return Vector2f(y, x);
			}
		}
	}
	return Vector2f(0, 0);
}

//parcours le tableau MyCase et renvoie la case la plus proche du joueur
Vector2f Game::distanceBetweenCase(bool isPlayer)
{
	int distance1 = 200;
	Vector2f tempCase;
	int a;
	int b;
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			// calcule de distance : \sqrt{ (x2 - x1)^ { 2 } + (y2 - y1)^ { 2 } }
			float distance = sqrt(pow(myCase[x][y].x - AllPlayer[Playeri].getPosition().x, 2) + pow(myCase[x][y].y - AllPlayer[Playeri].getPosition().y, 2));
			if (distance < distance1)
			{
				distance1 = distance;
				tempCase = myCase[x][y];
				a = x;  b = y;
			}
		}
	}
	if (isPlayer) inCase[a][b] = 1;
	return tempCase;
}

//si on touche un enemy
bool Game::degatEnemy()
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 6; x++)
		{
			if (inCase[y][x] == -1)
			{
				if (inCase[y - 1][x] == 1 && inCase[y + 1][x] == 1)
				{
					cout << "Kill" << endl;
					enemyIndex = getEnemy(myCase[y][x]);
					Playeri = getPlayer(myCase[y - 1][x]);
					playerIndex = getPlayer(myCase[y + 1][x]);
					inCase[y][x] = 0;
					//state = playerAttack;
					setState(playerAttack);
					return true;
				}
				if (inCase[y][x - 1] == 1 && inCase[y][x + 1] == 1)
				{
					cout << "Kill" << endl;
					enemyIndex = getEnemy(myCase[y][x]);
					Playeri = getPlayer(myCase[y][x - 1]);
					playerIndex = getPlayer(myCase[y][x + 1]);
					AllPlayer[Playeri].Attack();
					inCase[y][x] = 0;
					//state = playerAttack;
					setState(playerAttack);
					return true;
				}
			}
		}
	}
	return false;
}

//pour avoir l'index de l'enemie qu'il nous faut dans la list de allEnemy
int Game::getEnemy(Vector2f pos)
{
	for (int i = 0; i < allEnemy.size(); i++)
	{
		if (allEnemy[i].getPosition() == pos)
		{
			//cout << i << endl;
			return i;
		}
	}
}

int Game::getPlayer(Vector2f pos)
{
	for (int i = 0; i < AllPlayer.size(); i++)
	{
		if (AllPlayer[i].getPosition() == pos)
		{
			//cout << i << endl;
			return i;
		}
	}
}

void Game::update(float dt) {
	//AllPlayer[playerIndex].playerTextureMovee(+1);
	//AllPlayer[2].playerTextureMovee(-1);

	/*if (state == playerTurn) time -= dt;
	if (time <= 0) state = enemyTurn;*/

	/*if (enemydie)
	{
	if(attckPlayer)  attckPlayer = AllPlayer[Playeri].Attack();

	if (attckPlayer == false)
	{
	allEnemy[enemyIndex].Die(dt);
	if (allEnemy[enemyIndex].destroy)
	{
	allEnemy.erase(allEnemy.begin() + enemyIndex);
	enemydie = false;
	}
	}
	}*/

	switch (state)
	{
	case playerStartAttack:
		//AllPlayer[playerIndex].bStart();
		if (!AllPlayer[playerIndex].bTransition()) setState(playerAttack);
		break;
	case playerAttack:
		AllPlayer[playerIndex].Attack();
		if (!AllPlayer[Playeri].Attack()) setState(playerKill);
		//state = playerKill;
		break;
	case playerKill:
		allEnemy[enemyIndex].Die(dt);
		if (allEnemy[enemyIndex].destroy)
		{
			allEnemy.erase(allEnemy.begin() + enemyIndex);
			enemydie = false;
			setState(playerTurn);
			//state = playerTurn;
		}
		break;
	default:
		break;
	}

	for (auto i = partPlayer.begin(); i != partPlayer.end();)
	{
		particule& p = *i;
		p.update(dt);
		if (p.destroy)
			i = partPlayer.erase(i);
		else
			i++;
	}
}

void Game::draw(RenderWindow& win) {
	win.draw(bg);
	//playercol.draw(win);
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
	for (particule& p : partPlayer)
	{
		win.draw(p.part);
	}

	for (Enemy& e : allEnemy)
	{
		e.draw(win);
	}

	for (player& p : AllPlayer) {
		p.draw(win);
	}
}

void Game::setState(State st) {
	state = st;

	switch (state)
	{
	case playerTurn:
		AllPlayer[Playeri].color(Color::Black);
		AllPlayer[playerIndex].color(Color::Black);
		break;
	case enemyTurn:
		break;
	case playerAttack:
		AllPlayer[Playeri].color(Color::Yellow);
		AllPlayer[playerIndex].color(Color::Yellow);
		break;
	case playerKill:
		AllPlayer[Playeri].color(Color::Red);
		AllPlayer[playerIndex].color(Color::Red);
		break;
	default:
		break;
	}
}
