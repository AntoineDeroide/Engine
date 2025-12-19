#ifndef ENGINE_CORE_COMPLEXCONTAINERS_ARRAY_H
#define ENGINE_CORE_COMPLEXCONTAINERS_ARRAY_H

template <typename T, unsigned int size_T>
class Array
{
public:
	Array();
	~Array();
	
	// COPY
	Array(Array& const _other);
	Array operator=(Array& const _other);
	
	// MOVE
	Array(Array&& _other);
	Array operator=(Array&& _other);

	void Assign(unsigned int _index, T _data);
	void Erase(unsigned int _index);

	bool IsEmpty();

	T At(unsigned int _index);
	T operator[](unsigned int _index);

private:
	T data[];
	unsigned int capacity;
};

#endif // ENGINE_CORE_COMPLEXCONTAINERS_ARRAY_H