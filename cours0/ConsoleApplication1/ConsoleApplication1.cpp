// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <functional>
#include <string>
#include "Vec2.hpp"
#include "Vec2T.h"
#include "Vec3T.h"
#include "arr.h"
#include "DynArr.h"
#include "Node.h"

using namespace std;

void subFunc()
{
	arr<int> * foo = new arr<int>(4);

	cout << foo->get(0) << endl;

	delete foo;
}

void subFunc1()
{
	/*DynArr<int> foo(4);
	cout << foo.get(0) << endl;
	foo.get(0) = 33;
	cout << foo.get(0) << endl;

	foo.resize(13);

	for (int i = 0; i < 10; i++)
	{
		cout << foo.get(i) << endl;
	}

	foo.set(12, 9);
	cout << foo.get(12) << endl;*/

	Node* root = new Node(10);
	root = root->heapify(9);
	root = root->heapify(11);
	root = root->heapify(12);

	if (!root->isOk()) throw " root is not a valid heap";

	root = Node::merge(root, new Node(12));
	root = Node::merge(root, new Node(12));

	Node* n = new Node(1, new Node(2), new Node(3));
	n = n->deleteMin();
	if(!n->isOk()) throw " root is not a valid heap";

	//root = root->deleteMin();
	root = root->remove(12);
	if (!root->isOk()) throw " root is not a valid heap";

	auto stop = 6;

}

int StringLengh(const char * str) {
	int compt = 0;
	while (*str != 0)
	{
		compt++;
		str++;
	}
	cout << compt << endl;
	return compt;
}

void StringCopy(char* dst, const char* src)
{
	while (*src) //while value(src) is not zero
	{
		/*char dstchar = *dst;
		*dst = dstchar;*/
		*dst = *src;//copy value(src) in value (dst

		dst++;
		src++;
	}
}

void subFunc2()
{
	char tot2[5] = "toto";
	auto k = 0;
	int nb = StringLengh(tot2);

	char sapin[128] = {};
	StringCopy(sapin, "lapin");
	cout << sapin << endl;
}

DynArr<float> * doHeapSort(float* tab, int tabSize)
{
	DynArr<float> * f = new DynArr<float>(tabSize);
	Node * root = new Node(tab[0]);
	for (int i = 1; i < tabSize; ++i)
	{
		root = root->heapify(tab[i]);
	}
	int idx = 0;
	while (root)
	{
		float val = root->getMin();
		f->set(idx, val);
		root = root->deleteMin();
		idx++;
	}
	return f;
	/*DynArr<float> * f = new DynArr<float>(tabSize);
	Node * root = Node::fromTabRec(tab, tabSize);
	int idx = 0;
	while (root)
	{
		float val = root->getMin();
		f->set(idx, val);
		root = root->deleteMin();
		idx++;
	}*/

	//return f;
}

void heapSort() {

	float tf[4] = { 1.0, 15.0, -1.0, 25.0 };
	DynArr<float> * tab = doHeapSort(tf, 4);

	for (int i = 0; i < 4; i++)
	{
		cout << tab->get(i) << " ";
	}
	cout << endl;
}

void subFunction3() {
	DynArr<float>tab(0);
	for (int i = 0; i < 10; i++)
	{
		tab.set(i, i);
	}
	tab.Reverse();
	tab.push_back(16);

	DynArr<float>tab0(0);
	tab0.push_back(66);
	tab.append(tab0);

	std::function<void(float)> affiche = [](float elem)
	{
		printf("%f ", elem);
	};
	tab.iter(affiche);
	printf("\n");

	auto k = 0;
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

	//subFunc();

	//subFunc1();

	//subFunc2();

	//heapSort();

	subFunction3();


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
