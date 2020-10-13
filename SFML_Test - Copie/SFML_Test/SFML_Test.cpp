// sfml_test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> // inclut un entete/header appelé iostream

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;

int main()
{
    std::cout << "Hello World!\n";
    sf::RenderWindow window(sf::VideoMode(640, 480, 32), "SFML works!");

    sf::Text text;

    sf::Font font;
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
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                //ajouter un point
            }

        }
        //dessiner le tableau de point avec la classe sf:: VertexArray

        //afficher la doc

        // "Backspace pour remettre les point a 0"
        // "Nb de points courants"

        text.setFont(font);
        text.setString("toto");
        text.setCharacterSize(24);
        text.setPosition(10, 10);
        text.setFillColor(sf::Color::White);

        window.clear();

        window.draw(text);
        //window.draw(mespoints);
        //window.draw(montexte de docs);
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
