// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//


#include <iostream>
#include <functional>
#include <string>
#include <cstdlib>

#include "pch.h"
#include "Vec2.hpp"
#include "Vec2T.h"
#include "Vec3T.h"
#include "arr.h"
#include "DynArr.h"
#include "Node.h"
#include "IntArray.h"

using namespace std;

void subFunc()
{
	arr<int>* foo = new arr<int>(4);

	cout << foo->get(0) << endl;

	delete foo;
}

void test()
{
	IntArray foo(4);
	foo.get(0) = 12;
	foo.get(1) = 14;
	foo.get(2) = 34;
	foo.get(3) = 36;
	foo.push_back(6);
	foo.push_front(9);
	foo.insert(2, 89);
	//foo.get(6) = 69;
	for (int i = 0; i < foo.allocSize; i++)
	{
		cout << foo.data[i] << endl;
	}
	//cout << foo.search(34) << endl;
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
	if (!n->isOk()) throw " root is not a valid heap";

	//root = root->deleteMin();
	root = root->remove(12);
	if (!root->isOk()) throw " root is not a valid heap";

	auto stop = 6;

}

int StringLengh(const char* str) {
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

void Mency(char* dst, char* src, int size)
{
	for (int i = 0; i < size; i++)
	{
		*dst = *src;
		dst++;
		src++;
	}
}
//rechercher le char ou les chaines dans le contenu
char* StrChr(char* grange, char chat)
{
	//tant que valeur grange ne veut pas 0
	//si on a le bon caractere renvoyé le pointeur courant
	//sinon avancer grange
	//retourner nullptr
	while (*grange != 0)
	{
		if (chat == *grange)
		{
			return grange;
		}
		grange++;
	}
	return nullptr;
}

//renvoie true sur meule commence par aiguille
//sinon envoie false
bool startsWith(char* meule, char* aiguille)
{
	int longueurMeule = StringLengh(meule);
	int longueuraiguille = StringLengh(aiguille);

	if (longueurMeule > longueurMeule) return false;
	for (int i = 0; i < StringLengh(aiguille); i++)
	{
		if (aiguille[i] != meule[i])
		{
			return false;
		}
	}
	return true;
	//pour chaque character de aiguille
	//	si meule est fini
	//		renvoie faux

	//on a trouvé 

}
char* StrStr(char* meule, char* aiguille)
{
	//si meule commence par aiguille
	//on a trouvé
	//rest de la meule = avancer meule
	//sinon on appel recursivement strstr sur le reste de la meule
	if (aiguille == nullptr && meule == nullptr)return nullptr;
	if (meule == nullptr) return nullptr;
	if (*meule == 0) return nullptr;

	if (startsWith(meule, aiguille))
	{
		return meule;
	}
	else
	{
		return StrStr(meule + 1, aiguille);
	}
}

int add(int a, int b)
{
	//on a le droit a 0 1 et operation + 1
	//
	//transformer l'appel en recursion
	//plutot que d'écrire return a+b
	//appeler (a+1) b fois
	//a + b => (a+1), (b-1) ... b fois jusque b = 0 dans ce cas renvoyer a

	/*if (b == 0) return a;
	a = a + 1;
	b= b - 1;
	return add(a, b);*/

	if (b == 0)
		return a;
	if (b < 0)
		return -1 + add(a, b + 1);
	else
		return 1 + add(a, b - 1);

}

int sub(int a, int b)
{
	/*if (b == 0) return a;
	a = a - 1;
	b = b - 1;
	return sub(a, b);*/

	if (b == 0)
		return a;
	if (b < 0)
		return -1 + sub(a, b - 1);
	else
	{
		return add(a, -b);
	}
}

int mul(int a, int b)
{
	if (b == 0) return 0;
	if (b < 0)
		return -a + mul(a, b + 1);
	else
		return a + mul(a, b - 1);
}

int divition(int a, int b)
{
	if (b == 0) return 0;
	if (b == 1) return a;

	if (b < 0) return  -divition(a, -b);
	if (a < 0) return  -divition(-a, b);

	if (a < b) return 0;

	else
	{
		return 1 + divition(a - b, b); // div(a,b)  => 1 + (a-b) / b
	}

}

int modulo(int a, int b)
{
	if (b == 0) return 0;
	if (b == 1) return 0;

	if (b < 0) return  -modulo(a, -b);
	if (a < 0) return  -modulo(-a, b);

	if (a < b) return a;
	else
	{
		return modulo(a - b, b);
	}
}

//1 si a est supérieur lexicographiquement
//0 si a est égal lexicographiquement
//-1 si a est inférieur lexicographiquement
int StrCmp(const char* a, const char* b)
{
	// si a est vide et b est vide
	if (*a == 0 && *b == 0) return 0;
	if (*a == 0) return -1; //si a vide
	if (*b == 0) return 1; //si b vide

	/*
	//si valeur(a) > valeur(b)
	if(*a == *b)
		return StrCmp(a+1, b+1);
	else
		return ((*b - *a) > 0) ? -1 : 1;
	*/

	if (*a < *b)
		return -1;
	if (*a > * b)
		return 1;
	else
		return StrCmp(a + 1, b + 1);
}

void subFunction5()
{
	/*cout << add(5, 6) << endl;
	cout << sub(5, 6) << endl;
	cout << mul(4, -5) << endl;
	cout << divition(10, 2) << endl;
	cout << divition(-10, 2) << endl;
	cout << modulo(5, 3) << endl;

	cout << modulo(15, 7) << endl;
	cout << modulo(-15, 7) << endl;
	cout << modulo(15, 20) << endl;
	cout << modulo(15, 3) << endl;*/
	cout << StrCmp("c", "a") << endl;
}

void subFunction4()
{
	char data[] = { 1,2,3,4,5,6 };
	char* dest = (char*)malloc(16);
	for (int i = 0; i < 16; i++) dest[i] = 0;

	Mency(dest, data, sizeof(data) * sizeof(char));

	for (int i = 0; i < 16; i++)
	{
		cout << (int)dest[i] << endl;
	}
	free(dest);

	char forest[] = "sapinsapin";
	char sapin[] = "sapin";

	if (startsWith(forest, sapin))
		printf("fores begin with sapin");
	else
	{
		printf("error");
	}

	char pin[] = "pin";
	char* res = strstr(forest, pin);
	if (res != nullptr)
		printf("after pin in the forest");
	else
	{
		printf("error");
	}


}

DynArr<float>* doHeapSort(float* tab, int tabSize)
{
	DynArr<float>* f = new DynArr<float>(tabSize);
	Node* root = new Node(tab[0]);
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
	DynArr<float>* tab = doHeapSort(tf, 4);

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

	//subFunction3();
	//subFunction5();

	test();


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