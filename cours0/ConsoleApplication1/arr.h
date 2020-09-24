#pragma once

template<typename T>
class arr {
public:
	T* data;
	int size = 0;
	arr(int _size)
	{
		this->size = _size;
		data = new T[_size];
		for (int i = 0; i < size; i++)
		{
			data[i] = {};
		}
	}

	virtual ~arr( )
	{
		delete[] data;
		cout << "deleted" << endl;
	}

	T get(int idx)
	{
		if (idx >= size) throw "out of bound maj";
		if (idx < 0) throw "out of bound min";
		return data[idx];
	}

	void set(int idx, T val)
	{
		if (idx >= size) throw "out of bound maj";
		if (idx < 0) throw "out of bound min";
		data[idx] = val;
	}
};
