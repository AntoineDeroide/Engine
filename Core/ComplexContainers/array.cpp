#include "array.h"

template <typename T, unsigned int size_T>
Array<T, size_T>::Array() : data(nullptr), capacity(size_T)
{
	data = new T[capacity];
}

template <typename T, unsigned int size_T>
Array<T, size_T>::~Array()
{
	delete[] data;
	capacity = 0;
}

/// COPY

template <typename T, unsigned int size_T>
Array<T, size_T>::Array(Array& const _other)
{
	data = new T[_other.capacity];

	if (_other.capacity > size_T)
	{
		for (int i = 0; i < size_T; i++)
			data[i] = _other[i];
	}
	else if (_other.capacity < size_T)
	{
		for (int i = 0; i < _other.capacity; i++)
			data[i] = _other[i];
	}
}

template <typename T, unsigned int size_T>
Array<T, size_T> Array<T, size_T>::operator=(Array& const _other)
{
	capacity = size_T;
	data = new T[_other.capacity];

	if (_other.capacity > size_T)
	{
		for (int i = 0; i < size_T; i++)
			data[i] = _other[i];
	}
	else if (_other.capacity < size_T)
	{
		for (int i = 0; i < _other.capacity; i++)
			data[i] = _other[i];
	}
}

/// MOVE

template <typename T, unsigned int size_T>
Array<T, size_T>::Array(Array&& const _other)
{
	capacity = size_T;
	data = new T[capacity];
	if (_other.capacity > size_T)
	{
		for (int i = 0; i < size_T; i++)
			data[i] = _other[i];
	}
	else if (_other.capacity < size_T)
	{
		for (int i = 0; i < _other.capacity; i++)
			data[i] = _other[i];
	}

	_other.~Array();
}

template <typename T, unsigned int size_T>
Array<T, size_T> Array<T, size_T>::operator=(Array&& const _other)
{
	capacity = size_T;
	data = new T[capacity];
	if (_other.capacity > size_T)
	{
		for (int i = 0; i < size_T; i++)
			data[i] = _other[i];
	}
	else if (_other.capacity < size_T)
	{
		for (int i = 0; i < _other.capacity; i++)
			data[i] = _other[i];
	}

	_other.~Array();
}


template <typename T, unsigned int size_T>
void Array<T, size_T>::Assign(unsigned int _index, T _data)
{
	if (IsEmpty() == true or _index > capacity) return;

	data[_index] = _data;
}

template <typename T, unsigned int size_T>
void Array<T, size_T>::Erase(unsigned int _index)
{
	if (IsEmpty() == true or _index > size_T or _index < 0) return;

	data[_index] = T();
}

template <typename T, unsigned int size_T>
bool Array <T, size_T>::IsEmpty()
{
	if (size_T == 0) return true;

	for (int i = 0; i < size_T; i++)
	{
		if (data[i] != T())
			return false;
	}

	return true;
}

template <typename T, unsigned int size_T>
T Array<T, size_T>::At(unsigned int _index)
{
	for (int i = 0; i < size_T; i++)
	{
		if (i == _index)
			return data[i];
	}

	return T();
}

template <typename T, unsigned int size_T>
T Array<T, size_T>::operator[](unsigned int _index)
{
	for (int i = 0; i < size_T; i++)
	{
		if (i == _index)
			return data[i];
	}

	return T();
}

