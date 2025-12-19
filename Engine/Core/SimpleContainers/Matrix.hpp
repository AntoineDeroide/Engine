#include "Vector.hpp"

struct Matrix
{
	float _11, _12, _13, _14,
		_21, _22, _23, _24,
		_31, _32, _33, _34,
		_41, _42, _43, _44;

	Matrix() = default;
	
	Matrix() :
		_11(0.0f), _12(0.0f), _13(0.0f), _14(0.0f),
		_21(0.0f), _22(0.0f), _23(0.0f), _24(0.0f),
		_31(0.0f), _32(0.0f), _33(0.0f), _34(0.0f),
		_41(0.0f), _42(0.0f), _43(0.0f), _44(0.0f)
	{};

	Matrix(float b_11, float b_12, float b_13, float b_14,
		float b_21, float b_22, float b_23, float b_24,
		float b_31, float b_32, float b_33, float b_34,
		float b_41, float b_42, float b_43, float b_44) :
		_11(b_11), _12(b_12), _13(b_13), _14(b_14),
		_21(b_21), _22(b_22), _23(b_23), _24(b_24),
		_31(b_31), _32(b_32), _33(b_33), _34(b_34),
		_41(b_41), _42(b_42), _43(b_43), _44(b_44)
	{};
	
	~Matrix() = default;

	//////////////////////////////////////////
	// COPY
	Matrix(Matrix& const other) 
	{
		_11 = other._11; _12 = other._12; _13 = other._13; _14 = other._14; 
		_21 = other._21; _22 = other._22; _23 = other._23; _24 = other._24; 
		_31 = other._31; _32 = other._32; _33 = other._33; _34 = other._34; 
		_41 = other._41; _42 = other._42; _43 = other._43; _44 = other._44;
	};
	Matrix operator=(Matrix& const other) 
	{
		_11 = other._11; _12 = other._12; _13 = other._13; _14 = other._14;
		_21 = other._21; _22 = other._22; _23 = other._23; _24 = other._24;
		_31 = other._31; _32 = other._32; _33 = other._33; _34 = other._34;
		_41 = other._41; _42 = other._42; _43 = other._43; _44 = other._44;
	};
	//////////////////////////////////////////
	// MOVE
	Matrix(Matrix&& other) 
	{
		_11 = other._11; _12 = other._12; _13 = other._13; _14 = other._14;
		_21 = other._21; _22 = other._22; _23 = other._23; _24 = other._24;
		_31 = other._31; _32 = other._32; _33 = other._33; _34 = other._34;
		_41 = other._41; _42 = other._42; _43 = other._43; _44 = other._44;

		other.Identity();
	};
	Matrix operator=(Matrix&& other) 
	{
		_11 = other._11; _12 = other._12; _13 = other._13; _14 = other._14;
		_21 = other._21; _22 = other._22; _23 = other._23; _24 = other._24;
		_31 = other._31; _32 = other._32; _33 = other._33; _34 = other._34;
		_41 = other._41; _42 = other._42; _43 = other._43; _44 = other._44;

		other.Identity();
	};
	//////////////////////////////////////////

	// Transpose la matrice
	void Transpose() 
	{
		Matrix temp = Matrix(*this);
	
		_12 = temp._21;
		_13 = temp._31;
		_14 = temp._41;
		
		_21 = temp._12;
		_23 = temp._32;
		_24 = temp._42;
	
		_31 = temp._13;
		_32 = temp._23;
		_34 = temp._43;
		
		_41 = temp._14;
		_42 = temp._24;
		_43 = temp._34;

		temp.~Matrix();
	};

	// Retourne la matrice transposee, sans modifier l'objet (interet ?)
	Matrix GetTranspose() const
	{

	}; 

	float GetValue(unsigned int row, unsigned int col) const {};
	Vector4f GetColumn(unsigned int index) const {};
	Vector4f GetLine(unsigned int index) const {};

	float SetValue(unsigned int row, unsigned int col) const {};
	
	Matrix Identity() {}; // Set la matrice a l'identite
	Matrix GetIdentity() const {}; // Retourne la matrice identite, sans modifier l'objet

};