// sfml_test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> // inclut un entete/header appelé iostream
#include <vector> // inclut un entete/header appelé iostream

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;


int main()
{
    std::cout << "Hello World!\n";
    sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "SFML works!");

    sf::Text text;
    sf::VertexArray line;
    sf::Font font;
    std::vector<Vector2f> myPoints;

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
                if (event.key.code == sf::Keyboard::BackSpace)
                {
                    line.clear();
                    /*for (int i = 0; i < myPoints.size(); i++)
                    {
                        myPoints[i] = sf::Vector2f(0, 0);
                    }*/
                }
                //si backspace 
                //reset tout les points
                //myPoints.clear()
                myPoints.clear();
            }

            if (event.type == sf::Event::MouseButtonPressed) {              
                //ajouter un point
                myPoints.push_back(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                line.clear();
                line.setPrimitiveType(sf::PrimitiveType::Lines);

				for (Vertex& vtx : myPoints)
				{
					line.append(vtx);
				}
                /*for (int i = 1; i < myPoints.size(); i++)
                {
                    line.append(sf::Vertex(myPoints[i-1], sf::Color(0x5DFFA3ff)));
                    line.append(sf::Vertex(myPoints[i], sf::Color(0x5DFFA3ff)));
                    std::cout <<"x :" << myPoints[i].x << std::endl;
                    std::cout <<"y : " << myPoints[i].y << std::endl;
                }*/

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

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
