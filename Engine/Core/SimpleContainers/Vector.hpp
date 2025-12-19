#include <iostream>

struct Vector2f
{
#ifdef _DEBUG || DEBUG
	void Debug() 
	{ 
		std::cout << "[x : " << x << "; y : " << y << "]\n"; 
	}
#endif

	float x, y;

	float* Data() const
	{
		float toReturn[2] = { x, y };

		return toReturn;
	}

	Vector2f(float _x = 0.0f, float _y = 0.0f) :
		x(_x), 
		y(_y) 
	{};

	//////////////////////////////////////////
	// COPY
	Vector2f(Vector2f& const _other)
	{
		x = _other.x;
		y = _other.y;
	};
	Vector2f operator=(Vector2f& const _other)
	{
		x = _other.x;
		y = _other.y;
	};
	//////////////////////////////////////////
	
	//////////////////////////////////////////
	// MOVE
	Vector2f(Vector2f&& _other)
	{
		x = _other.x;
		y = _other.y;

		_other.~Vector2f();
	};
	Vector2f operator=(Vector2f&& _other)
	{
		x = _other.x;
		y = _other.y;

		_other.~Vector2f();
	};
	///////////////////////////////////////////
	
	~Vector2f() = default;

	///////////////
	// OPERATORS //
	///////////////

	Vector2f operator+(Vector2f _other)
	{
		return Vector2f(
			x + _other.x, 
			y + _other.y
		);
	};
	
	Vector2f operator+=(Vector2f _other)
	{
		x += _other.x;
		y += _other.y;

		return *this;
	};

	Vector2f operator-(Vector2f _other)
	{
		return Vector2f(
			x - _other.x, 
			y - _other.y
		);
	};


	Vector2f operator-=(Vector2f _other)
	{
		x -= _other.x;
		y -= _other.y;

		return *this;
	};


	Vector2f operator*(float _multiplier)
	{
		return Vector2f(
			x * _multiplier, 
			y * _multiplier
		);
	};


	Vector2f operator*=(float _multiplier)
	{
		x *= _multiplier;
		y *= _multiplier;

		return *this;
	};


	Vector2f operator/(float _divider)
	{
		return Vector2f(
			x / _divider, 
			y / _divider
		);
	};


	Vector2f operator/=(float _divider)
	{
		x /= _divider;
		y /= _divider;

		return *this;
	};

	bool operator<(Vector2f _other)
	{
		if (x > _other.x and y > _other.y) return true;
		return false;
	};

	bool operator<=(Vector2f _other)
	{
		if (x >= _other.x and y >= _other.y) return true;
		return false;
	};

	bool operator>(Vector2f _other)
	{
		if (x < _other.x and y < _other.y) return true;
		return false;
	};

	bool operator>=(Vector2f _other)
	{
		if (x <= _other.x and y <= _other.y) return true;
		return false;
	};
};

struct Vector3f
{
#ifdef _DEBUG || DEBUG
	void Debug()
	{
		std::cout << "[x : " << x << "; y : " << y << "; z : " << z << "]\n";
	}
#endif

	float x, y, z;

	float* Data() const
	{
		float toReturn[3] = { x, y, z };

		return toReturn;
	}

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) :
		x(_x), 
		y(_y), 
		z(_z) 
	{};

	//////////////////////////////////////////
	// COPY
	Vector3f(Vector3f& const _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
	};
	Vector3f operator=(Vector3f& const _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
	};
	//////////////////////////////////////////

	//////////////////////////////////////////
	// MOVE
	Vector3f(Vector3f&& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;

		_other.~Vector3f();
	};
	Vector3f operator=(Vector3f&& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;

		_other.~Vector3f();
	};
	///////////////////////////////////////////

	~Vector3f() = default;

	///////////////
	// OPERATORS //
	///////////////

	Vector3f operator+(Vector3f _other)
	{
		return Vector3f(
			x + _other.x, 
			y + _other.y, 
			z + _other.z
		);
	};

	Vector3f operator+=(Vector3f _other)
	{
		x += _other.x;
		y += _other.y;
		z += _other.z;

		return *this;
	};

	Vector3f operator-(Vector3f _other)
	{
		return Vector3f(
			x - _other.x, 
			y - _other.y, 
			z - _other.z
		);
	};


	Vector3f operator-=(Vector3f _other)
	{
		x -= _other.x;
		y -= _other.y;
		z -= _other.z;

		return *this;
	};


	Vector3f operator*(float _multiplier)
	{
		return Vector3f(
			x * _multiplier, 
			y * _multiplier, 
			z * _multiplier
		);
	};


	Vector3f operator*=(float _multiplier)
	{
		x *= _multiplier;
		y *= _multiplier;
		z *= _multiplier;

		return *this;
	};


	Vector3f operator/(float _divider)
	{
		return Vector3f(
			x / _divider, 
			y / _divider, 
			z / _divider
		);
	};


	Vector3f operator/=(float _divider)
	{
		x /= _divider;
		y /= _divider;
		z /= _divider;

		return *this;
	};
};

struct Vector4f
{
#ifdef _DEBUG || DEBUG
	void Debug()
	{
		std::cout << "[x : " << x << "; y : " << y << "; z : " << z << "; w : "<< w << "]\n";
	}
#endif

	float x, y, z, w;

	float* Data() const
	{
		float toReturn[4] = { x, y, z, w };

		return toReturn;
	}

	Vector4f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f) :
		x(_x), 
		y(_y), 
		z(_z), 
		w(_w) 
	{};

	//////////////////////////////////////////
	// COPY
	Vector4f(Vector4f& const _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
		w = _other.w;
	};
	Vector4f operator=(Vector4f& const _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
		w = _other.w;
	};
	//////////////////////////////////////////

	//////////////////////////////////////////
	// MOVE
	Vector4f(Vector4f&& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
		w = _other.w;

		_other.~Vector4f();
	};
	Vector4f operator=(Vector4f&& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
		w = _other.w;

		_other.~Vector4f();
	};
	///////////////////////////////////////////

	~Vector4f() = default;

	///////////////
	// OPERATORS //
	///////////////

	Vector4f operator+(Vector4f _other)
	{
		return Vector4f(
			x + _other.x,
			y + _other.y,
			z + _other.z,
			w + _other.w
		);
	};

	Vector4f operator+=(Vector4f _other)
	{
		x += _other.x;
		y += _other.y;
		z += _other.z;
		w += _other.w;

		return *this;
	};

	Vector4f operator-(Vector4f _other)
	{
		return Vector4f(
			x - _other.x, 
			y - _other.y, 
			z - _other.z, 
			w - _other.w
		);
	};


	Vector4f operator-=(Vector4f _other)
	{
		x -= _other.x;
		y -= _other.y;
		z -= _other.z;
		w -= _other.w;

		return *this;
	};


	Vector4f operator*(float _multiplier)
	{
		return Vector4f(x * _multiplier, y * _multiplier, z * _multiplier, w * _multiplier);
	};


	Vector4f operator*=(float _multiplier)
	{
		x *= _multiplier;
		y *= _multiplier;
		z *= _multiplier;
		w *= _multiplier;

		return *this;
	};


	Vector4f operator/(float _divider)
	{
		return Vector4f(
			x / _divider, 
			y / _divider, 
			z / _divider, 
			w / _divider
		);
	};


	Vector4f operator/=(float _divider)
	{
		x /= _divider;
		y /= _divider;
		z /= _divider;
		w /= _divider;

		return *this;
	};
};

/// Colors are defined between 0 and 255. For alpha, 255 is opaque and 0 is transparent.
struct Color 
{
	struct { 
		unsigned int r, g, b, a; 
	};

	Color() :
		r(0),
		g(0),
		b(0),
		a(0)
	{};
	Color(unsigned int _r, unsigned int _g, unsigned int _b, unsigned int _a) :
		r(_r),
		g(_g),
		b(_b),
		a(_a)
	{};

	///////////////////////////////////////////
	// COPY
	Color(Color& const _other)
	{
		r = _other.r;
		g = _other.g;
		b = _other.b;
		a = _other.a;
	}
	Color operator=(Color& const _other)
	{
		r = _other.r;
		g = _other.g;
		b = _other.b;
		a = _other.a;
	}
	///////////////////////////////////////////

	///////////////////////////////////////////
	// MOVE
	Color(Color&& _other)
	{
		r = _other.r;
		g = _other.g;
		b = _other.b;
		a = _other.a;

		_other.~Color();
	}
	Color operator=(Color&& _other)
	{
		r = _other.r;
		g = _other.g;
		b = _other.b;
		a = _other.a;

		_other.~Color();
	}
	///////////////////////////////////////////

	~Color() = default;

};

//constexpr struct {
//	Color RED     { 255, 0, 0, 255 }; // 255 0 0
//	Color GREEN   { 0, 255, 0, 255 }; // 0 255 0
//	Color BLUE    { 0, 0, 255, 255 }; // 0 0 255
//
//	Color YELLOW  { 255, 255, 0, 255 }; // 255 255 0
//	Color CYAN    { 0, 255, 255, 255 }; // 0 255 255
//	Color MAGENTA { 255, 0, 255, 255 }; // 255 0 255
//
//	Color WHITE   { 255, 255, 255, 255 }; // 255 255 255
//	Color BLACK   { 0, 0, 0, 255 }; // 0 0 0
//	Color CLEAR   { 0, 0, 0, 0 }; // 0 0 0 0
//} COLORS;