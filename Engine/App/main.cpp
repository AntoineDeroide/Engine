#include <iostream>

#include "../Core/SimpleContainers/Vector.hpp"


int main(int* argc, char** argv)
{
	Vector4f vec = Vector4f();

	vec.Debug();

	Vector4f other_vec(vec);

	other_vec.Debug();

	return 0;
}