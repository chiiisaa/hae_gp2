// sfml_test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> // inclut un entete/header appelé iostream

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Interp.hpp"


using namespace std;
using namespace sf;



int main()
{
	std::cout << "Hello World!\n";
	sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "SFML works!");

	sf::Text text;
	sf::VertexArray line;
	line.setPrimitiveType(sf::PrimitiveType::LineStrip);
	sf::Font font;
	//std::vector<Vector2f> myPoints;
	std::vector<Vertex> myPoints;
	Color color;
	vector<Color> myColor;

	if (!font.loadFromFile("res/MAIAN.TTF")) {
		std::cout << "ERROR NO FONT" << std::endl;
		return 1;
	}

	// charger une fonte ?
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed) {
				//si backspace 
				//reset tout les points
				//myPoints.clear()
				if (event.key.code == sf::Keyboard::BackSpace)
				{
					line.clear();
					myPoints.clear();
				}
				if (event.key.code == sf::Keyboard::F1)
				{

				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				//ajouter un point
				//Vertex vtx ;
				Vertex vtx = Vector2f(event.mouseButton.x, event.mouseButton.y);
				myPoints.push_back(vtx);
				line.append(vtx);
				//color = sf::Color(rand(), rand(), rand());
				myColor.push_back(sf::Color(rand(), rand(), rand()));
				//myPoints.push_back
			}

		}
		//dessiner le tableau de point avec la classe sf:: VertexArray

		//afficher la doc

		// "Backspace pour remettre les point a 0"
		// "Nb de points courants"

		text.setFont(font);
		text.setString("Touche Backspace pour supprimer les points");
		text.setCharacterSize(24);
		text.setPosition(0, 0);
		text.setFillColor(sf::Color::White);

		line.clear();
		if(myPoints.size() > 1)
		for (int i = 0; i < myPoints.size(); i++)
		{
			//recuperer vtx i-1
			Vertex v0 = (i == 0) ? myPoints[i] : myPoints[i - 1];
			//recuperer vtx i
			Vertex v1 = myPoints[i];
			//recuperer vtx i+1
			Vertex v2 = ((i + 1) >= myPoints.size()) ? myPoints[myPoints.size() - 1] : myPoints[i + 1];
			//recuperer vtx i+2
			Vertex v3 = ((i + 2) >= myPoints.size()) ? myPoints[myPoints.size() - 1] : myPoints[i + 2];

			//pour j de 0...20
			//	inserer catmull(v i-1,v i, v i+1, vi+2, j/20.0)
			for (int j = 0; j <= 20; j++)
			{
				float t = j / 20.0;
				Vector2f pos = Interp::c2(v0.position, v1.position, v2.position, v3.position, t);
				line.append(Vertex(pos, myColor[i]));
			}

			/*sf::Vertex p0(myPoints[i]);

			sf::Vector2f inter = Interp::lerp(myPoints[i].position, myPoints[i+1].position,0.5);
			inter.x += rand() % 50;
			inter.y += rand() % 50;
			sf::Vertex p01(inter, sf::Color::White);
			sf::Vertex p1(myPoints[i + 1]);
			line.append(p0);
			line.append(p01);
			line.append(p1);*/
		}

		/*for (int i = 0; i < myPoints.size() - 1; i++)
		{
			sf::Vertex p0(myPoints[i]);
			sf::Vertex p01(Interp::lerp(myPoints[i].position, myPoints[i + 1].position, 0.5), sf::Color::Red);
			sf::Vertex p1(myPoints[i + 1]);
			line.append(p0);
			line.append(p01);
			line.append(p1);
		}*/
		//A
		/* Mode immediate
		line.clear();
		line.setPrimitiveType(sf::PrimitiveType::Lines);
		line.append(sf::Vertex(sf::Vector2f(50, 50), sf::Color(0x5DFFA3ff)));
		line.append(sf::Vertex(sf::Vector2f(500, 500), sf::Color(0xF5363Cff)));*/
		//b moode retained
		/*VertexArray line(PrimitiveType::Lines, 2);
		line[0] = Vertex(Vector2f(50, 50), Color(0x5DFFA3ff));
		line[1] = Vertex(Vector2f(500, 500), Color(0xF5363Cff));*/

		window.clear();

		window.draw(text);
		window.draw(line);

		window.display();
	}

	return 0;
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
