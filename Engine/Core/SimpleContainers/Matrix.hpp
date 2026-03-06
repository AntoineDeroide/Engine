#include "Vector.hpp"

struct Matrix4x4
{
	float _00, _01, _02, _03,
		  _10, _11, _12, _13,
		  _20, _21, _22, _23,
		  _30, _31, _32, _33;

	float** _values;

	Matrix4x4(
		float b_00 = 0.0f, float b_01 = 0.0f, float b_02 = 0.0f, float b_03 = 0.0f,
		float b_10 = 0.0f, float b_11 = 0.0f, float b_12 = 0.0f, float b_13 = 0.0f,
		float b_20 = 0.0f, float b_21 = 0.0f, float b_22 = 0.0f, float b_23 = 0.0f,
		float b_30 = 0.0f, float b_31 = 0.0f, float b_32 = 0.0f, float b_33 = 0.0f) :
		_00(b_00), _01(b_01), _02(b_02), _03(b_03),
		_10(b_10), _11(b_11), _12(b_12), _13(b_13),
		_20(b_20), _21(b_21), _22(b_22), _23(b_23),
		_30(b_30), _31(b_31), _32(b_32), _33(b_33),
		_values(nullptr)
	{
		_values = new float* [4];
		for (int i = 0; i < 3; i++)
			_values[i] = new float[4];

		_values[0][0] = b_00; _values[0][1] = b_01; _values[0][2] = b_02; _values[0][3] = b_03;
		_values[1][0] = b_10; _values[1][1] = b_11; _values[1][2] = b_12; _values[1][3] = b_13;
		_values[2][0] = b_20; _values[2][1] = b_21; _values[2][2] = b_22; _values[2][3] = b_23;
		_values[3][0] = b_30; _values[3][1] = b_31; _values[3][2] = b_32; _values[3][3] = b_33;
	};
	
	~Matrix4x4() = default;

	//////////////////////////////////////////
	// COPY
	Matrix4x4(Matrix4x4& const other) 
	{
		_00 = other._00; _01 = other._01; _02 = other._02; _03 = other._03; 
		_10 = other._10; _11 = other._11; _12 = other._12; _13 = other._13; 
		_20 = other._20; _21 = other._21; _22 = other._22; _23 = other._23; 
		_30 = other._30; _31 = other._31; _32 = other._32; _33 = other._33;
	};
	Matrix4x4 operator=(Matrix4x4& const other) 
	{
		_00 = other._00; _01 = other._01; _02 = other._02; _03 = other._03;
		_10 = other._10; _11 = other._11; _12 = other._12; _13 = other._13;
		_20 = other._20; _21 = other._21; _22 = other._22; _23 = other._23;
		_30 = other._30; _31 = other._31; _32 = other._32; _33 = other._33;
	};
	//////////////////////////////////////////
	// MOVE
	Matrix4x4(Matrix4x4&& other) 
	{
		_00 = other._00; _01 = other._01; _02 = other._02; _03 = other._03;
		_10 = other._10; _11 = other._11; _12 = other._12; _13 = other._13;
		_20 = other._20; _21 = other._21; _22 = other._22; _23 = other._23;
		_30 = other._30; _31 = other._31; _32 = other._32; _33 = other._33;

		other.Identity();
	};
	Matrix4x4 operator=(Matrix4x4&& other) 
	{
		_00 = other._00; _01 = other._01; _02 = other._02; _03 = other._03;
		_10 = other._10; _11 = other._11; _12 = other._12; _13 = other._13;
		_20 = other._20; _21 = other._21; _22 = other._22; _23 = other._23;
		_30 = other._30; _31 = other._31; _32 = other._32; _33 = other._33;

		other.Identity();
	};
	//////////////////////////////////////////

	// Transpose la matrice
	void Transpose() 
	{
		Matrix4x4 temp = Matrix4x4(*this);
	
		_01 = temp._10;
		_02 = temp._20;
		_03 = temp._30;
		
		_10 = temp._01;
		_12 = temp._21;
		_13 = temp._31;
	
		_20 = temp._02;
		_21 = temp._12;
		_23 = temp._32;
		
		_30 = temp._03;
		_31 = temp._13;
		_32 = temp._23;
	};

	// Retourne la matrice transposee, sans modifier l'objet (interet ?)
	Matrix4x4 GetTranspose() const
	{

	}; 

	float GetValue(unsigned int row, unsigned int col) const {};
	Vector4f GetColumn(unsigned int index) const {};
	Vector4f GetLine(unsigned int index) const {};

	float SetValue(unsigned int row, unsigned int col) const {};
	
	// Retourne la matrice identite, sans modifier l'objet
	static Matrix4x4 Identity() 
	{
		return Matrix4x4(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		);
	
	};
	// Set la matrice a l'identite
	void SetIdentity() 
	{
		(*this) = Identity();
	}; 
};

struct Matrix3x3
{
public:
	Matrix3x3(
		float b_00 = 0.0f, float b_01 = 0.0f, float b_02 = 0.0f,
		float b_10 = 0.0f, float b_11 = 0.0f, float b_12 = 0.0f,
		float b_20 = 0.0f, float b_21 = 0.0f, float b_22 = 0.0f
	) :
		_00(b_00), _01(b_01), _02(b_02),
		_10(b_10), _11(b_11), _12(b_12),
		_20(b_20), _21(b_21), _22(b_22)
	{};
	~Matrix3x3() = default;

	Vector3f operator[](int _index) const
	{
		return Vector3f();
	}

private:
	float _00, _01, _02,
		  _10, _11, _12,
		  _20, _21, _22;
};