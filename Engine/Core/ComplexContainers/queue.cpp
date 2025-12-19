#include "queue.h"

template <typename T>
Queue<T>::Queue<T>(int _startingCapacity) : 
	data(nullptr),
	capacity(_startingCapacity),
	size(0)
{
	// code...
}

template <typename T>
Queue<T>::~Queue()
{
	delete[] data;
	capacity = 0;
	size = 0;
}

/// COPY
template <typename T>
Queue<T>::Queue(Queue<T>& const _other)
{
	int loop_range = (size > _other.size) ? _other.size : size;
	capacity = (capacity > _other.capacity) ? capacity : _other.capacity;

	for (int i = 0; i < loop_range; i++)
		data[i] = other[i];
}

template <typename T>
Queue<T> Queue<T>::operator=(Queue<T>& const _other)
{
	int loop_range = (size > _other.size) ? _other.size : size;
	capacity = (capacity > _other.capacity) ? capacity : _other.capacity;

	for (int i = 0; i < loop_range; i++)
		data[i] = other[i];
}

template <typename T>
Queue<T>::Queue(Queue<T>&& _other)
{

}

/// MOVE
template <typename T>
Queue<T> Queue<T>::operator=(Queue<T>&& _other)
{



}