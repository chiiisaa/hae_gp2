#include "Game.hpp"

Game::Game(RenderWindow* win)
{
	this->win = win;
	Lv.loadLevel(0);

	bg = RectangleShape(Vector2f(win->getSize().x, bg.getSize().y));
	bool isOK = text.loadFromFile("images/bg.jpg");
	if (!isOK)
	{
		auto erg = 66;
	}
	bg.setTexture(&text);
	bg.setSize(Vector2f(640, 960));

	for (int i = 0; i < Lv.Perso.at("Personage"); i++)
	{
		Player.setPosition(myCase[Lv.PositionPerso.at(i).x][Lv.PositionPerso.at(i).y]);
		inCase[Lv.PositionPerso.at(i).x][Lv.PositionPerso.at(i).y] = 1;
		AllPlayer.push_back(Player);
	}

	//Player.setPosition(myCase[1][1]);
	/*player = RectangleShape(Vector2f(64, 64));
	player.setFillColor(Color(0xEB2C4C));
	player.setOrigin(25, 25);
	player.setPosition(50, 50);*/
	//AllPlayer.push_back(Player);

	/*player2 = RectangleShape(Vector2f(64, 64));
	player2.setFillColor(Color(0xEB2C4C));
	player2.setOrigin(25, 25);
	player2.setPosition(myCase[5][5]);*/

	//AllPlayer.push_back(Player);

	/*Player.setPosition(myCase[5][5]);
	AllPlayer.push_back(Player);

	Player.setPosition(myCase[6][5]);
	AllPlayer.push_back(Player);*/

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
	/*en.setPosition(myCase[5][4]);
	allEnemy.push_back(en);
	en.setPosition(myCase[2][2]);
	allEnemy.push_back(en);*/

	for (int i = 0; i < Lv.Perso.at("Enemy"); i++)
	{
		en.setPosition(myCase[Lv.PositionE.at(i).x][Lv.PositionE.at(i).y]);
		inCase[Lv.PositionE.at(i).x][Lv.PositionE.at(i).y] = -1;
		allEnemy.push_back(en);
	}

	/// Temp
	/*inCase[5][4] = -1;
	inCase[2][2] = -1;*/
	/*inCase[5][5] = 1;
	inCase[1][1] = 1;
	inCase[6][5] = 1;*/

	/// temp,teste
	font.loadFromFile("res/MAIAN.TTF");
	stateString.setFont(font);
	stateString.setFillColor(Color::Red);
	stateString.setString("State :");
	tempsText.setFont(font);
	tempsText.setFillColor(Color::Green);
	tempsText.setPosition(stateString.getPosition() + Vector2f(300, 0));

	setState(playerTurn);
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

	/// <summary>
	/// TESTE Enemy movement
	/// </summary>
	/// <param name="ev"></param>
	if (ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == Keyboard::Key::T)
		{
			//changeLevel();
			Nextbool = !Nextbool;
			//allEnemy[enemyIndex].attack(AllPlayer[Playeri].getPosition(),0.001);


			//allEnemy[enemyIndex].looseHp(5);

			/*Vector2f Enemypos = SearchValueInMyCase(allEnemy[enemyIndex].getPosition());
			cout << "E pos x : " << Enemypos.x << endl;
			allEnemy[enemyIndex].move(allEnemy[enemyIndex].getPosition(), Enemypos, myCase, myCase[7][5]);
			cout << allEnemy[enemyIndex ].getPosition().x << " " << allEnemy[enemyIndex].getPosition().y << endl;*/
		}
	}

	if (Nextbool)
	{
		change();
		if (ev.type == Event::MouseButtonReleased)
		{
			if (ev.mouseMove.x > NextText.getPosition().x - 20 && ev.mouseMove.x < NextText.getPosition().x + 40
				&& ev.mouseMove.y > NextText.getPosition().y - 20 && ev.mouseMove.y < NextText.getPosition().y + 40)
			{
				changeLevel();
				time = 5;
				state = playerTurn;
				Nextbool = false;
			}
		}
	}

	if (state == playerTurn)
	{
		if (ev.type == Event::MouseButtonPressed)
		{
			for (int i = 0; i < AllPlayer.size(); i++)
			{
				Vector2f mouseHitPlayer = AllPlayer[i].getPosition();
				if (ev.mouseButton.x > mouseHitPlayer.x - 32 && ev.mouseButton.x < mouseHitPlayer.x + 32 && ev.mouseButton.y > mouseHitPlayer.y - 32 && ev.mouseButton.y < mouseHitPlayer.y + 32)
				{
					playercol.setPosition(AllPlayer[i].getPosition());
					inCase[(int)SearchValueInMyCase(AllPlayer[i].getPosition()).x][(int)SearchValueInMyCase(AllPlayer[i].getPosition()).y] = 0;
					//ChangeValueInCase(AllPlayer[i].getPosition(), 0);
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
				//particulePlayer(distanceBetweenCase(false));
				particulePlayer(Vector2f(ev.mouseMove.x, ev.mouseMove.y));
			}
		}

		if (ev.type == Event::MouseButtonReleased && mouseInPlayer)
		{
			AllPlayer[Playeri].setPosition(distanceBetweenCase(true));
			mouseInPlayer = false;
			if (!degatEnemy()) setState(enemyTurn);
		}
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
			//ChangeValueInCase(casetemp, 0);
			p.setPosition(LastPlayerPos);
			casetemp = SearchValueInMyCase(Vector2f(p.getPosition().x, p.getPosition().y));
			inCase[(int)casetemp.x][(int)casetemp.y] = 1;
			//ChangeValueInCase(casetemp, 1);
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

void Game::ChangeValueInCase(Vector2f target, int value)
{
	Vector2f val = SearchValueInMyCase(target);
	inCase[(int)val.x][(int)val.y] = value;
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
					enemyIndex = getEnemy(myCase[y][x]);
					Playeri = getPlayer(myCase[y - 1][x]);
					playerIndex = getPlayer(myCase[y + 1][x]);
					b.setShape(false);
					b.setPos(myCase[y][x]);
					inCase[y][x] = 0;
					setState(playerStartAttack);
					return true;
				}
				if (inCase[y][x - 1] == 1 && inCase[y][x + 1] == 1)
				{
					enemyIndex = getEnemy(myCase[y][x]);
					Playeri = getPlayer(myCase[y][x - 1]);
					playerIndex = getPlayer(myCase[y][x + 1]);
					b.setShape(true);
					b.setPos(myCase[y][x]);
					inCase[y][x] = 0;
					setState(playerStartAttack);
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
			return i;
		}
	}
}

float timeForEnemy = 1.0; //Temp
Vector2f EnemyStartMovePos;
void Game::update(float dt) {

	if (state != enemyTurn)
	{
		time -= dt;
		tempsText.setString("time : " + std::to_string(time)); // Temporaire
		if (time <= 0)
		{
			tempsText.setString("time : 0");
			if (mouseInPlayer)
			{
				//AllPlayer[Playeri].setPosition(LastPlayerPos);
				AllPlayer[Playeri].setPosition(distanceBetweenCase(true));
				mouseInPlayer = false;
			}
			if (state == playerTurn)
			{
				time = 5.00;
				setState(enemyTurn);
			}
		}
	}
	int randNum;
	switch (state)
	{
	case playerStartAttack:
		if (!b.bTransition()) setState(playerAttack);
		break;
	case playerAttack:
		!AllPlayer[playerIndex].Attack();
		if (!AllPlayer[Playeri].Attack()) setState(playerKill);
		break;
	case playerKill:
		randNum = rand() % (10 - 30 + 1) + 10;
		cout << randNum << endl;
		degat.setFont(font);
		degat.setFillColor(Color::Yellow);
		degat.setString(std::to_string(randNum));
		degat.setPosition(allEnemy[enemyIndex].getPosition());
		allEnemy[enemyIndex].looseHp(randNum);
		if (allEnemy[enemyIndex].die)
		{
			allEnemy[enemyIndex].Die(dt);
			if (allEnemy[enemyIndex].destroy)
			{
				allEnemy.erase(allEnemy.begin() + enemyIndex);
				cout << "allEnemy.size() : " << allEnemy.size() << endl;
				if (allEnemy.size() <= 0)
				{
					Nextbool = true;
					//changeLevel();
					setState(playerTurn);
				}
				else setState(enemyTurn);
			}
		}
		else setState(enemyTurn);
		break;
	case enemyTurn:
		timeForEnemy -= dt;
		if (timeForEnemy <= 0)
		{
			timeForEnemy = 1.0;

			Vector2f Enemypos = SearchValueInMyCase(allEnemy[enemyIndex].getPosition());
			player p = allEnemy[enemyIndex].FindPlayer(AllPlayer);
			Vector2f target = allEnemy[enemyIndex].p(SearchValueInMyCase(p.getPosition()), myCase, EnemyStartMovePos,inCase);
			cout << EnemyStartMovePos.x << " " <<EnemyStartMovePos.y << endl;
			Vector2f targetpos = SearchValueInMyCase(target);
			/*allEnemy[enemyIndex].createsNodes(myCase, inCase, Enemypos);
			allEnemy[enemyIndex].dij_process(targetpos, inCase, myCase);
			//allEnemy[enemyIndex].vvv(myCase);
			allEnemy[enemyIndex].movee(allEnemy[enemyIndex].getPosition(), Enemypos, myCase, targetpos, inCase);
			auto pos = 0;*/

			if (allEnemy[enemyIndex].move(Enemypos, myCase, targetpos, inCase))
			{
				inCase[(int)SearchValueInMyCase(target).x][(int)SearchValueInMyCase(target).y] = -1;
				AllPlayer[getPlayer(p.getPosition())].looseHp(5);
				setState(playerTurn);
				//setState(enemyAttack);
			}

			/*timeForEnemy = 1.0;
			Vector2f Enemypos = SearchValueInMyCase(allEnemy[enemyIndex].getPosition());
			inCase[(int)Enemypos.x][(int)Enemypos.y] = 0;
			//ChangeValueInCase(Enemypos, 0);
			//Vector2f target = myCase[4][5];
			Vector2i temp = allEnemy[enemyIndex].SearchPosAttackPlayer(inCase);
			Vector2f target = myCase[temp.x][temp.y];
			//cout << " target : " << target.x << " " << target.y << endl;
			if (allEnemy[enemyIndex].move(allEnemy[enemyIndex].getPosition(), Enemypos, myCase, target, inCase))
			{
				inCase[(int)SearchValueInMyCase(target).x][(int)SearchValueInMyCase(target).y] = -1;
				//ChangeValueInCase(target,-1);
				//setState(enemyAttack);
				AllPlayer[Playeri].looseHp(10);
				setState(playerTurn);
			}*/
		}
		break;
	case enemyAttack:
		if (allEnemy[enemyIndex].attack(AllPlayer[Playeri].getPosition(), dt)) setState(playerTurn);
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

	b.draw(win);
	//temp
	win.draw(stateString);
	win.draw(tempsText);

	if (Nextbool)
	{
		win.draw(bgNextLevel);
		win.draw(NextText);
		win.draw(Victoire);
	}

}

void Game::setState(State st) {
	state = st;

	switch (state)
	{
	case playerTurn:
		//AllPlayer[Playeri].color(Color::Black);
		//AllPlayer[playerIndex].color(Color::Black);
		stateString.setString("State: playerTurn");
		break;
	case enemyTurn:
		EnemyStartMovePos = allEnemy[enemyIndex].getPosition();
		tempsText.setString("time : 0");
		time = 5.00;
		stateString.setString("State: enemyTurn");
		break;
	case playerAttack:
		//AllPlayer[Playeri].color(Color::Yellow);
		//AllPlayer[playerIndex].color(Color::Yellow);
		//stateString.setString("State: playerAttack");
		break;
	case playerKill:
		//AllPlayer[Playeri].color(Color::Red);
		//AllPlayer[playerIndex].color(Color::Red);
		//tateString.setString("State: playerKill");
		break;
	default:
		break;
	}
}

void Game::change()
{
	bgNextLevel = RectangleShape(Vector2f(640, 960));
	NextText.setFont(font);
	NextText.setFillColor(Color::Blue);
	NextText.setString("Next");
	//NextText.setPosition(640/2, 960/2);
	Victoire.setFont(font);
	Victoire.setFillColor(Color::Yellow);
	Victoire.setString("Win");
	Victoire.setPosition(640 / 2, 960 / 2);
}

void Game::changeLevel()
{
	AllPlayer.clear();
	allEnemy.clear();
	Lv.nextLevel();
	for (int i = 0; i < Lv.Perso.at("Personage"); i++)
	{
		Player.setPosition(myCase[Lv.PositionPerso.at(i).x][Lv.PositionPerso.at(i).y]);
		inCase[Lv.PositionPerso.at(i).x][Lv.PositionPerso.at(i).y] = 1;
		AllPlayer.push_back(Player);
	}

	for (int i = 0; i < Lv.Perso.at("Enemy"); i++)
	{
		en.setPosition(myCase[Lv.PositionE.at(i).x][Lv.PositionE.at(i).y]);
		inCase[Lv.PositionE.at(i).x][Lv.PositionE.at(i).y] = -1;
		allEnemy.push_back(en);
	}
}
