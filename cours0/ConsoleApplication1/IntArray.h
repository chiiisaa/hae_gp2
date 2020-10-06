#pragma once

#include <functional>

class IntArray
{
public:
	int* data = nullptr;
	int allocSize = 0;

	//faire un tableau de data
	IntArray(int size)
	{
		this->allocSize = size;
		data = (int*)malloc(size * sizeof(int));
		//data = new int[size];
		for (int i = 0; i < size; i++)
		{
			data[i] = {};
		}
	};

	IntArray(const IntArray& arr)
	{
		int size = arr.allocSize;
		data = (int*)malloc(size * sizeof(int));
		this->allocSize = size;
		for (int i = 0; i < size; i++)
		{
			data[i] = arr.data[i];
		}

	}

	// faire un delete
	virtual ~IntArray()
	{
		free(data);
	}

	//faire un rezize
	void resize(int size)
	{

	}


	//faire un get
	int& get(int index) {
		if (index >= allocSize) throw "assert :: out of bound";
		if (index < 0) throw "out of bound min";
		return data[index];
	}

	//faire un set
	int& set(int index) {
		resize(index + 1);
		return data[index];
	}

	//faire un operator[]
	int& operator[] (int idx)
	{
		return data[idx];
	}

	static IntArray iota(int sz)
	{

	}

	//faire une recherche linéaire
	//renvoie -1 si pas trouvé
	//renvoie la position si trouvée
	//int search(int key)
	//

};
