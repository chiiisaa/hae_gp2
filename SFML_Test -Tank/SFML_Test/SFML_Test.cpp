// sfml_test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> // inclut un entete/header appelé iostream

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Interp.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;


int main()
{
	cout << "Hello World!\n";
	sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "SFML works!");
	Font font;

	if (!font.loadFromFile("res/MAIAN.TTF")) {
		cout << "ERROR NO FONT" << endl;
		return 1;
	}

	Game g(&window);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			g.processInput(event);
		g.update();
		window.clear();
		g.draw(window);
		window.display();
	}

	return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
