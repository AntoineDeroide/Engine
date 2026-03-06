#ifndef ENGINE_CORE_COMPLEXCONTAINERS_QUEUE_H
#define ENGINE_CORE_COMPLEXCONTAINERS_QUEUE_H

template <typename T>
class Queue
{

/// <summary>
/// Principe First in, first out. File d'attente
/// </summary>
public:
	Queue(int _startingCapacity);
	~Queue();
	
	// COPY
	Queue(Queue<T>& const _other);
	Queue<T> operator=(Queue<T>& const _other);

	// MOVE
	Queue(Queue<T>&& _other);
	Queue<T> operator=(Queue<T>&& _other);


	T& operator[](unsigned int _index);
	void Resize();

private:
	bool NeedResize();

	T data[];
	int capacity; // nbre d'emplacements reserves
	int size; // nbre d'elements
};


#endif // ENGINE_CORE_COMPLEXCONTAINERS_QUEUE_H