// sfml_test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> // inclut un entete/header appelé iostream

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Interp.hpp"
#include "totue.hpp"

using namespace std;
using namespace sf;


int main()
{
	std::cout << "Hello World!\n";
	sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "SFML works!");
	tortue to;
	tortue posTemp;
	vector<Cmd> cmds;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == (Keyboard::Left))to.turnLeft();
				if (event.key.code == (Keyboard::Right))to.turnRight();
				if (event.key.code == (Keyboard::Up))to.avancer(30);
				if (event.key.code == (Keyboard::Down));

				if (event.key.code == sf::Keyboard::Key::R) {
					to.reset();
					posTemp.reset();
				}

				if (event.key.code == sf::Keyboard::Key::T) {
					cmds = { Cmd::Advance, Cmd::Advance, Cmd::TurnLeft45, Cmd::Advance};
					cout << "Taoe" << endl;
					for (int i = 0; i < cmds.size() ; i)
					{
						cout << i << endl;
						window.clear();
						int time = 1000;
						vector<Cmd> temp = { cmds[i] };
						posTemp.setPos(to.getpos());
						posTemp.play(temp);
						//posTemp.draw(window);

						to.play(temp);
						to.draw(window);
						window.display();

						while (time >= 0)
						{
							cout << time << endl;
							time -= 1;
						}
						i++;
					}

					/*for (int i = 1; i < 2; i)
					{
						cout << cmds.size() << endl;
						Cmd temp = cmds[1];
						//posTemp.setPos(to.getpos());
						to.play2(temp);

						/*if (to.getpos() == posTemp.getpos())
						{
							cout << "i" << endl;
							posTemp.play2(temp);
							i++;
						}
					}*/

					//to.reset();
					//to.play(cmds);
				}
			}
		}

		window.clear();
		to.draw(window);
		window.display();
	}

	return 0;
}

Vector2f directionFromAngle(float angle) {
	Vector2f dir;
	dir.x = cos(angle);
	dir.y = sin(angle);
	return dir;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
