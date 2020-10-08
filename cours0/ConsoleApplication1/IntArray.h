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
	~IntArray()
	{
		free(data);
	}

	//faire un rezize
	void resize(int newAllocSize)
	{
		if (newAllocSize < allocSize)
			return;

		int allocSizeByte = newAllocSize * sizeof(int);
		data = (int*)realloc(data, allocSizeByte);

		for (int i = allocSize; i < newAllocSize; i++)
		{
			data[i] = {};
		}

		allocSize = newAllocSize;
	}




	//faire un get
	int& get(int index) {
		if (index >= allocSize) throw "assert :: out of bound";
		if (index < 0) throw "out of bound min";
		return data[index];
	}

	//faire un set
	int& set(int index) {
		if (index >= allocSize)
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
		IntArray arr(sz);
		for (int i = 0; i < sz; i++){
			arr.data[i] = i;
		}
		return arr;
	}

	static IntArray random(int sz)
	{
		IntArray arr(sz);
		for (int i = 0; i < sz; i++)
		{
			arr.data[i] = rand();
		}
		return arr;
	}

	//devors : search, push_first , push_back
	//
	//faire une recherche linéaire
	//renvoie -1 si pas trouvé
	//renvoie la position si trouvée
	//int search(int key)
	//

	int search(int key)
	{
		for (int i = 0; i < allocSize; i++)
		{
			if (key == data[i]) return i;
		}
		return -1;
	}

	//offset the array and
	//
	//void push_back (int val)
	void push_back(int val)
	{
		resize(allocSize + 1);
		for (int i = allocSize - 1; i > 0; i--)
		{
			get(i) = get(i - 1);
		}
		get(0) = val;
	}
	//void push_front (int val)
	void push_front(int val)
	{
		set(allocSize) = val;
		/*(allocSize + 1);
		get(allocSize - 1) = val;*/
	}
	//void insert (int pos,int val)
	void insert(int pos, int val)
	{
		if (pos == 0) push_back(val);
		if (pos == allocSize - 1) push_front(val);
		else
		{
			resize(allocSize + 1);
			for (int i = allocSize - 1; i > pos; i--)
			{
				get(i) = get(i - 1);
			}
			get(pos) = val;
		}
	}

	//recherche de position d'insertion
	//renvoie la position ou inserer dans le tableau si il etait trié 
	//int searchInsertionPos(int key)

	int searchInsertinPos(int key)
	{

	}

};
