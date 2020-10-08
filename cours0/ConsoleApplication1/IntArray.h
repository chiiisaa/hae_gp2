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

	int searchRec(int key, int startPos = 0)
	{
		if (key == data[startPos]) return startPos;
		if (key >= startPos) return -1;
		else searchRec(key, startPos + 1);

	}

	//offset the array and
	//
	//void push_back (int val)
	void push_back(int val)
	{
		int pos = allocSize;
		resize(allocSize + 1);
		data[pos] = val;

	}
	//void push_front (int val)
	void push_front(int val)
	{
		resize(allocSize + 1);
		for (int i = allocSize - 1; i > 0; i--)
		{
			get(i) = get(i - 1);
		}
		get(0) = val;
	}
	//void insert (int pos,int val)
	void insert(int pos, int val)
	{
		resize(allocSize + 1);
		for (int i = allocSize - 1; i >= pos; i--)
		{
			data[i] = data[i - 1];
		}
		data[pos] = val;
	}

	//recherche de position d'insertion
	//on condidereque le tableau est trié
	//renvoie la position ou inserer la valeur dans le tableau si il etait trié 
	//int searchInsertionPos(int key)

	int searchInsertinPos(int key)
	{
		for (int i = 0; i < allocSize; i++)
		{
			if (key < data[i])
			{
				return i;
			}
		}
	}


	int searchInsertinPosRec(int key, int pos = 0)
	{
		if (pos >= allocSize) return allocSize;
		else if (data[pos] >= key) return pos;
		else return searchInsertinPosRec(key, pos + 1);
	}

	/*int searchInsertinPosRec(int key, int pos = 0)
	{
		if (pos >= allocSize) return allocSize;
		if (key == data[pos]) return pos;

		if (pos >= allocSize - 1)
		{
			if (key < data[pos])
			{
				return pos ;
			}
			else
			{
				return allocSize;
			}

		}
		//if (pos < allocSize - 1)
		else
		{
			if (data[pos] < key)
			{
				if (data[pos + 1] < key)
					return searchInsertinPosRec(key, pos + 1);
				if (data[pos + 1] >= key)
					return pos + 1;
			}
			else {
				if (data[pos] > key)
					return key;
			}
			/*if (data[pos] < key && data[pos + 1] < key)
				return searchInsertinPosRec(key, pos + 1);

			if (data[pos] < key && data[pos + 1] > key)
				return pos + 1;
			
			if (data[pos] > key)
				return pos;
			
		}

	}*/

	//retourne faux si deux element du tableau ne sont pas triés
	//sinon retourn true
	bool isSorted()
	{
		for (int i = 0; i < allocSize; i++)
		{
			if (data[i] > data[i + 1]) return false;
		}
		return true;
	}

	bool isSortedRec(int pos = 0)
	{
		if (pos >= allocSize - 1)
			return true;

		if (data[pos] < data[pos + 1]) return isSortedRec(pos + 1);
			
		return false;
		
	}



	static IntArray sort(int* data, int dataSize);

	static IntArray sortInPlace(int* data, int dataSize);

	bool binarySearch(int key, int start, int end)
	{
		//retourne vrai si on a retrouvé la clée 
		//sinon faux
		int mid = (end + start + 1) / 2;

		if (end < start) return false;

		if (data[start] == key) return true;
		if (data[end] == key) return true;
		if (data[mid] == key) return true;

		if (data[mid] > key)
			return binarySearch(key, start, mid - 1);

		return binarySearch(key, mid + 1,end);

		/*int milieu = start / end;
		if (milieu == key) return true;
		else if (milieu < key) binarySearch(key, start, milieu - 1);
		else if (milieu > key) binarySearch(key, milieu + 1, end);
		
		if (end < start) return false;*/
	}

};
