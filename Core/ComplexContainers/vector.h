#ifndef ENGINE_CORE_COMPLEXCONTAINERS_VECTOR_H
#define ENGINE_CORE_COMPLEXCONTAINERS_VECTOR_H

template <typename T>
class Vector
{
public :
	Vector();
	~Vector();
	
	Vector(Vector& const other);
	Vector operator=(Vector& const other);
	
	Vector(Vector&& other);
	Vector operator=(Vector&& other);
	
	bool Resize();
	void Clear();
	void ShrinkToFit(unsigned int new_size);

	void PushBack(T item);
	void PopBack();
	T& At(unsigned int index);
	T& operator[](unsigned int index);

	T& Begin();
	T& End();

	bool IsEmpty();

private:
	T data[];
	unsigned int size; // nbre d'elements (emplacements utilises)
	unsigned int capacity; // nombre d'emplacements reserves
};

#endif // ENGINE_CORE_COMPLEXCONTAINERS_VECTOR_H