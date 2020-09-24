// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "Vec2.hpp"
#include "Vec2T.h"
#include "Vec3T.h"
#include "arr.h"

using namespace std;

void subFunc()
{
	arr<int> * foo = new arr<int>(4);

	cout << foo->get(0) << endl;

	delete foo;
}

int main()
{
	/*Vec2 a(16, 23);

	Vec2T<int> t0(4, 4);
	Vec2T<int> t1(4, 4);

	auto tres = t1.Add(t0);

	Vec3T<int> t3(3, 3, 3);
	Vec3T<int> t4(5, 5, 5);

	auto t = t3.ADD(t4);

	cout << to_string(tres.x) << endl;

	Vec2T<char> vc0('a', 'b');
	Vec2T<char> vc1('c', 'd');
	auto vcres = vc0.Add(vc1);

	cout << string(1, 'a') << endl;
	cout << string(1, vcres.x) << string(1, vcres.y) << endl;
	auto end = 0;

	int tab[] = { 0,1,2,3 };
	int szTab = sizeof(tab) / sizeof(int);
	for (int i = 0; i < szTab; i++)
	{
		cout << tab[i];
	}

	int* c0 = tab;
	int* c1 = &(tab[0]);

	int valC = *c0++;

	Vec2 de(33, 44);
	Vec2 dee(55, 55);
	de.incr(&dee);
	cout << to_string(dee.x) << endl;

	Vec2* c = new Vec2(66,0);

	cout << endl;*/

	subFunc();

	cout << endl;
}


// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
