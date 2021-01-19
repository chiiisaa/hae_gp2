#include "Game.hpp"

Game::Game(RenderWindow* win)
{
	this->win = win;
	Lv.loadLevel(0);

	bg = RectangleShape(Vector2f(win->getSize().x, bg.getSize().y));
	end = RectangleShape(Vector2f(win->getSize().x, bg.getSize().y));
	bool isOK = text.loadFromFile("images/bg.jpg");
	if (!isOK)
	{
		auto erg = 66;
	}
	bg.setTexture(&text);
	bg.setSize(Vector2f(640, 960));

	textCredit.loadFromFile("images/Credit.png");
	end.setTexture(&textCredit);
	end.setSize(Vector2f(640, 960));
	winOrLose.setPosition(Vector2f(220, 20));
	winOrLose.setFont(font);
	winOrLose.setCharacterSize(80);
	exit.setPosition(Vector2f(220, 900));
	exit.setFont(font);
	exit.setCharacterSize(50);
	exit.setOutlineThickness(0.5);
	exit.setOutlineColor(Color::Black);
	exit.setString("EXIT");
	///
	for (int i = 0; i < Lv.numbreOfCharacter.at("Healer"); i++)
	{
		player PH(true);
		PH.setPosition(myCase[Lv.PositionHealer.at(i).x][Lv.PositionHealer.at(i).y]);
		inCase[Lv.PositionHealer.at(i).x][Lv.PositionHealer.at(i).y] = 1;
		AllPlayer.push_back(PH);
	}

	for (int i = 0; i < Lv.numbreOfCharacter.at("Personage"); i++)
	{
		Player.setPosition(myCase[Lv.PositionPerso.at(i).x][Lv.PositionPerso.at(i).y]);
		inCase[Lv.PositionPerso.at(i).x][Lv.PositionPerso.at(i).y] = 1;
		AllPlayer.push_back(Player);
	}

	for (int i = 0; i < Lv.numbreOfCharacter.at("Healer"); i++)
	{
		AllPlayer[i].SetHealer();
	}


	//player3.insert(player3.begin() + 5, player);

	LigneX = RectangleShape(Vector2f(5, 640));
	LigneX.setOrigin(0, 0);
	LigneX.setFillColor(Color::White);
	LigneY = RectangleShape(Vector2f(480, 5));
	LigneY.setOrigin(0, 0);
	LigneY.setFillColor(Color::White);

	for (int i = 0; i < Lv.numbreOfCharacter.at("Enemy"); i++)
	{
		en.setPosition(myCase[Lv.PositionE.at(i).x][Lv.PositionE.at(i).y]);
		inCase[Lv.PositionE.at(i).x][Lv.PositionE.at(i).y] = -1;
		en.setTurn(Lv.EnemyTurn[i]);
		allEnemy.push_back(en);
	}
	/*for (int i = 0; i < Lv.numbreOfCharacter.at("Enemy"); i++)
	{
		allEnemy[i].turn = Lv.EnemyTurn[i];
	}*/

	/// temp,teste
	font.loadFromFile("res/MAIAN.TTF");
	attackText.setFont(font);
	attackText.setOrigin(32, 32);
	attackText1.setFont(font);
	attackText1.setOrigin(32, 32);
	stateText.setFont(font);
	stateText.setFillColor(Color::Red);
	stateText.setString("State :");
	tempsText.setFont(font);
	tempsText.setFillColor(Color::Green);
	tempsText.setPosition(stateText.getPosition() + Vector2f(300, 0));

	click.openFromFile("sons/Menu_Selection_Click.wav");

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

	if (ev.type == Event::KeyPressed) {
		if (ev.key.code == Keyboard::Key::H)
		{
			AllPlayer[0].setPosition(Vector2f(286, 324));
		}
	}

	/// <summary>
	/// TESTE Enemy movement
	/// </summary>
	/// <param name="ev"></param>
	if (ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == Keyboard::Key::T)
		{
			//Nextbool = !Nextbool;
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
				Nextbool = false;
				click.play();
				setState(playerTurn);
			}
		}
	}

	if (state == lose || state == Win)
	{
		if (ev.type == Event::MouseMoved)
		{
			if (ev.mouseMove.x > exit.getPosition().x - 20 && ev.mouseMove.x < exit.getPosition().x + 100
				&& ev.mouseMove.y > exit.getPosition().y - 15 && ev.mouseMove.y < exit.getPosition().y + 70)
			{
				exit.setFillColor(Color::Red);
			}
			else {
				exit.setFillColor(Color::White);
			}
		}
		if (ev.type == Event::MouseButtonPressed)
		{
			if (ev.mouseButton.x > exit.getPosition().x - 20 && ev.mouseButton.x < exit.getPosition().x + 100
				&& ev.mouseButton.y > exit.getPosition().y - 15 && ev.mouseButton.y < exit.getPosition().y + 70)
			{
				cout << "Close" << endl;
				win->close();
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
			if (!degatEnemy())
			{
				setState(enemyTurn);
			}
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
					setState(playerStartAttack);
					return true;
				}
			}
		}
	}
	return false;
}

void Game::AttackText(Vector2f pos, Vector2f pos1)
{
	attackText.setString("Attack");
	attackText.setPosition(pos);
	attackText1.setString("Attack");
	attackText1.setPosition(pos1);
	//attackText1.move(directionX, directionY);

	/*calcul : Longueur Vecteur |V|=racine carré de ((Vx * Vx) + (Vy * Vy))
normalisé Vecteur : U = V / |V|*/

}

void Game::AttackTextMove()
{
	Vector2f direction = Vector2f(attackText.getPosition().x - attackText1.getPosition().x, (attackText.getPosition().y - attackText1.getPosition().y));
	float norme = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction = direction / norme;

	attackText.move(-direction);
	attackText1.move(direction);
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

float timeForEnemy = 0.5; //Temp
Vector2f EnemyStartMovePos;
void Game::update(float dt) {
	if (state == playerTurn)
	{
		time -= dt;
		tempsText.setString("time : " + std::to_string(time)); // Temporaire
		if (time <= 0)
		{
			tempsText.setString("time : 0");
			if (mouseInPlayer) // si le temps = 0 et qu'on "déplace" encore le player avec la souris
			{
				AllPlayer[Playeri].setPosition(distanceBetweenCase(true)); // on met la position avec la case la plus proche 
				mouseInPlayer = false;
			}
			if (state == playerTurn)
			{
				time = 5.00;
				setState(enemyTurn);
			}
		}
	}
	else tempsText.setString("time : 0");
	//int randNum;
	switch (state)
	{
	case playerStartAttack:
		if (!b.bTransition())
		{
			AttackText(AllPlayer[playerIndex].getPosition(), AllPlayer[Playeri].getPosition());
			setState(playerAttack);
		}
		break;
	case playerAttack:
		AttackTextMove();

		if (AllPlayer[Playeri].healer || AllPlayer[playerIndex].healer)
		{
			iniDegat(4, 5, 10, allEnemy[enemyIndex].getPosition());
		}
		else iniDegat(4, 10, 25, allEnemy[enemyIndex].getPosition());

		AllPlayer[playerIndex].Attack();
		if (!AllPlayer[Playeri].Attack()) setState(playerKill);
		break;
	case playerKill:
		if (AllPlayer[Playeri].healer || AllPlayer[playerIndex].healer)
		{
			//if(soundEffects.getStatus() == sf::SoundSource::Status::Stopped) soundEffects.play();
			PlaysongOnce(soundEffects, "sons/heal.ogg");
			AllPlayer[Playeri].Heal(dt);
			AllPlayer[playerIndex].Heal(dt);
		}

		AttackTextMove();

		EnnemyDegat(dt);
		break;
	case enemyTurn:
		EnemyMove.clear();
		for (Enemy& e : allEnemy)
		{
			if (e.updateTurn())
			{
				EnemyMove.push_back(getEnemy(e.getPosition()));
			}
		}
		//enemyIndex = EnemyMove[0];

		if (EnemyMove.size() > 0)
		{
			EnemyStartMovePos = allEnemy[EnemyMove[0]].getPosition();
			setState(enemyok);
		}
		else setState(playerTurn);
		break;
	case enemyok:
		timeForEnemy -= dt;
		enemyIndex = EnemyMove[0];
		if (timeForEnemy <= 0)
		{
			timeForEnemy = 0.5;

			Vector2f Enemypos = SearchValueInMyCase(allEnemy[enemyIndex].getPosition());
			enemyTarget = allEnemy[enemyIndex].FindPlayer(AllPlayer);
			Vector2f target = allEnemy[enemyIndex].positionTarget(SearchValueInMyCase(enemyTarget.getPosition()), myCase, EnemyStartMovePos, inCase);
			Vector2f targetpos = SearchValueInMyCase(target);

			if (allEnemy[enemyIndex].move(Enemypos, myCase, targetpos, inCase))
			{
				inCase[(int)SearchValueInMyCase(target).x][(int)SearchValueInMyCase(target).y] = -1;
				EnemyStartMovePos = allEnemy[enemyIndex].getPosition();

				iniDegat(2, 10, 20, enemyTarget.getPosition());
				setState(enemyMove);
			}
		}
		break;
	case enemyMove:
	{
		if (allEnemy[enemyIndex].attack(enemyTarget.getPosition(), dt, EnemyStartMovePos)) setState(enemyAttack);

		break;
	}
	case enemyAttack:

		PlaysongOnce(soundEffects, "sons/Meow.ogg");
		AllPlayer[getPlayer(enemyTarget.getPosition())].Degat(dt);
		PlayerDegat(dt, enemyTarget);
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

	for (Text& t : degatText)
	{
		win.draw(t);
	}


	b.draw(win);

	win.draw(attackText);
	win.draw(attackText1);

	//temp
	win.draw(stateText);
	win.draw(tempsText);

	if (Nextbool)
	{
		win.draw(bgNextLevel);
		win.draw(NextText);
		win.draw(Victoire);
	}

	if (state == lose || state == Win)
	{
		win.draw(end);
		win.draw(winOrLose);
		win.draw(exit);
	}

}

void Game::setState(State st) {
	state = st;
	soundEffects.stop();

	switch (state)
	{
	case playerTurn:
		stateText.setString("State: playerTurn");
		break;
	case enemyTurn:
		//EnemyStartMovePos = allEnemy[enemyIndex].getPosition();
		tempsText.setString("time : 0");
		time = 5.00;
		stateText.setString("State: enemyTurn");
		break;
	case playerAttack:
		break;
	case playerKill:
		break;
	case lose:
		winOrLose.setString("Lose");
		winOrLose.setFillColor(Color::Red);
		break;
	case Win:
		winOrLose.setString("Win");
		winOrLose.setFillColor(Color::Yellow);
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
	enemyIndex = 0;
	for (int i = 0; i < Lv.numbreOfCharacter.at("Personage"); i++)
	{
		Player.setPosition(myCase[Lv.PositionPerso.at(i).x][Lv.PositionPerso.at(i).y]);
		inCase[Lv.PositionPerso.at(i).x][Lv.PositionPerso.at(i).y] = 1;
		AllPlayer.push_back(Player);
	}

	for (int i = 0; i < Lv.numbreOfCharacter.at("Enemy"); i++)
	{
		en.setPosition(myCase[Lv.PositionE.at(i).x][Lv.PositionE.at(i).y]);
		inCase[Lv.PositionE.at(i).x][Lv.PositionE.at(i).y] = -1;
		allEnemy.push_back(en);
	}
}
