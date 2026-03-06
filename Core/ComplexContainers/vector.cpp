#include "vector.h"

template <typename T>
Vector<T>::Vector<T>() : 
	data(nullptr), 
	size(0), 
	capacity(1)
{
	// code...
}


/// COPY
template <typename T>
Vector<T>::Vector<T>(Vector& const other) : Vector<T>()
{
	Clear();
	size = other.size;
	capacity = other.capacity;
	for (unsigned int i = 0; i < other.size; i++)
		data[i] = other.data[i];
};

template <typename T>
Vector<T> Vector<T>::operator=(Vector<T>& const other)
{
	Clear();
	size = other.size;
	capacity = other.capacity;
	for (unsigned int i = 0; i < other.size; i++)
		data[i] = other.data[i];
};

/// MOVE
template <typename T>
Vector<T>::Vector<T>(Vector<T>&& other) : data(nullptr), size(0), capacity(0)
{
	Clear();
	size = other.size;
	capacity = other.capacity;
	for (unsigned int i = 0; i < other.size; i++)
		data[i] = other.data[i];

	other.Clear();
	other.~Vector();
};

template <typename T>
Vector<T> Vector<T>::operator=(Vector<T>&& other)
{
	Clear();
	size = other.size;
	capacity = other.capacity;
	for (unsigned int i = 0; i < other.size; i++)
		data[i] = other.data[i];

	other.Clear();
	other.~Vector();
};

template <typename T>
Vector<T>::~Vector()
{
	delete[] data;
	size = 0;
	capacity = 0;
}
template <typename T>
bool Vector<T>::Resize()
{
	// Upsize()
	if (size >= capacity)
	{
		capacity *= 2;
		T new_data[] = new T[capacity];
		for (unsigned int i = 0; i < size; i++)
			new_data[i] = data[i];
		delete[] data;
		data = new_data;
		return true;
	}
	// Downsize()
	else if (size <= (capacity / 2))
	{
		capacity /= 2;
		T new_data[] = new T[capacity];
		for (unsigned int i = 0; i < size; i++)
			new_data[i] = data[i];
		delete[] data;
		data = new_data;
		return true;
	}

	return false;
}

template <typename T>
void Vector<T>::Clear()
{
	if (IsEmpty()) return;
	for (unsigned int i = 0; i < size; i++)
		delete data[i];
	size = 0;
	Resize();
}

template <typename T>
void Vector<T>::PushBack(T item)
{
	data[size] = item;
	size++;

	Resize();
};

template <typename T>
void Vector<T>::PopBack()
{
	if (IsEmpty()) return;
	delete data[size - 1];
	Resize();
};

template <typename T>
void Vector<T>::ShrinkToFit(unsigned int new_size)
{
	if (new_size > size)
	{
		size = new_size; 
		Resize();
	}
	else if (new_size < size)
	{
		Resize();
		T new_data[] = new T[new_size];
		for (unsigned int i = 0; i < new_size; i++)
			new_data[i] = data[i];
		delete[] data;
		data = new_data;
	}
}

template <typename T>
T& Vector<T>::At(unsigned int index)
{
	if (IsEmpty()) return nullptr;
	if (index <= size)
		return *(data[index]);
}

template <typename T>
T& Vector<T>::operator[](unsigned int index)
{
	if (IsEmpty()) return nullptr;
	if (index <= size)
		return *(data[index]);
}

template <typename T>
bool Vector<T>::IsEmpty()
{
	if (size == 0 and capacity == 0)
		return true;
	return false;
}

template<typename T>
T& Vector<T>::Begin()
{
	if (IsEmpty()) return &T();
	return data[0];
}

template<typename T>
T& Vector<T>::End()
{
	if (IsEmpty()) return nullptr;
	return data[size - 1];
}