#include "IntArray.h"
#include "pch.h"

/*IntArray IntArray::sort(int* data, int dataSize)
{
	IntArray arr(dataSize);
	arr.resize(dataSize);
	for (int i = 0; i < dataSize; i++)
	{
		int val = data[i];
		int pos = arr.searchInsertinPosRec(val);
		arr.insert(pos, val);
	}
}*/

IntArray IntArray::sortInPlace(int* data, int dataSize)
{
	//tri en place les valeurs
	//avoir un entier i
	//avoir un entier j
	//pour i 1 a datasize
	//	j=i
	//	tant que (j > 0 && arr(j) < arr(j - 1)
			//permuter(j,j-1)
	//	j--
	int i;
	int j;
	for (int i = 1; i < dataSize; i++)
	{
		j = i;
		while (j > 0 && data[j] < data[j-1])
		{
			int val = data[j-1];
			data[j-1] = data[j];
			data[j] = val;
			j--;
		}
	}


	/*for (int i = 0; i < dataSize - 1; i++)
	{
		for (int j = 0; j < dataSize; j++)
		{
			if (data[j] < data[i])
			{
				int val = data[i];
				data[i] = data[j];
				data[j] = val;
			}
		}
	}*/

}

