// SFML_Test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> // inclut un entete/header appelé iostream
#include <SFML/Graphics.hpp> //inclut un entete

int main() // fonction main 
{
    std::cout << "Hello World!\n"; //affiche à la console
    
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!"); //Crée la fenetre : 200x200 de titre SFML works!
    
    sf::CircleShape shape(100.f); // fait une variable circle : shape
    shape.setFillColor(sf::Color::Green); // on prend la variable "shape" et on la rempli en vert

    auto pos = shape.getPosition();
    sf::Vector2f dir(0, 0);
    while (window.isOpen())  // tant que la fenetre est ouvert
    {
        sf::Event event; // crée une variable event qu'on appelle event
        while (window.pollEvent(event)) // tant que window à un event
        {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A) shape.setFillColor(sf::Color::Blue);
                if (event.key.code == sf::Keyboard::B)
                {
                    shape.setFillColor(sf::Color::Red);
                }

                sf::Vector2f dir(0, 0);

                if (event.key.code == sf::Keyboard::Left) dir.x -= 1;
                if (event.key.code == sf::Keyboard::Right) dir.x += 1;
                if (event.key.code == sf::Keyboard::Up) dir.y += 1;
                if (event.key.code == sf::Keyboard::Down) dir.y -= 1;

                float len = sqrt(dir.x * dir.x + dir.y * dir.y);

                if (len) {
                    dir.x /= len;
                    dir.y /= len;

                    pos.x += dir.x;
                    pos.y += dir.y;
                }

                /*if (event.key.code == sf::Keyboard::Left) pos.x -= 1;
                if (event.key.code == sf::Keyboard::Right) pos.x += 1;
                if (event.key.code == sf::Keyboard::Up) pos.y += 1;
                if (event.key.code == sf::Keyboard::Down) pos.y -= 1; */
            }

            /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
                shape.setFillColor(sf::Color::Blue);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                shape.setFillColor(sf::Color::Black);*/

            if (event.type == sf::Event::MouseMoved)
            {
                pos.x = event.mouseMove.x - shape.getRadius();
                pos.y = event.mouseMove.y - shape.getRadius();
            }

            if (event.type == sf::Event::MouseWheelScrolled)
            {
                int radius = shape.getRadius();
                radius += event.mouseWheelScroll.delta;
                if (radius < 10) radius = 10;
                shape.setRadius(radius);

                std::cout << "wheel movement: " << event.mouseWheel.delta << std::endl;
                std::cout << "mouse x: " << event.mouseWheel.x << std::endl;
                std::cout << "mouse y: " << event.mouseWheel.y << std::endl;
            }

            if (event.type == sf::Event::Closed) // si l'event est = à fermer
                window.close(); // ferme la fenetre
        }

       

        /*if (event.key.code == sf::Keyboard::Left) dir.x -= 1;
        if (event.key.code == sf::Keyboard::Right) dir.x += 1;
        if (event.key.code == sf::Keyboard::Up) dir.y += 1;
        if (event.key.code == sf::Keyboard::Down) dir.y -= 1;

        float len = sqrt(dir.x * dir.x + dir.y * dir.y);

        float sp = 0.33;

        if (len > 0) {
            dir.x /= len;
            dir.y /= len;

            pos.x *= sp;
            pos.y *= sp;

        }*/
        
        window.clear(); // on efface
        window.draw(shape); // on dessine le shape
        shape.setPosition(pos);
        //auto pos = shape.getPosition();
        //pos.x += 0.01;
        //shape.setPosition(pos);
        window.display(); // affiche shape sur l'écran
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
