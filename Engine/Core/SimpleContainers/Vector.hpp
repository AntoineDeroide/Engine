struct Vector2f
{
	float x, y;

	Vector2f() : 
		x(0.0f), 
		y(0.0f) {};

	Vector2f(float b_x, float b_y) : 
		x(b_x), 
		y(b_y) 
	{};

	Vector2f(int b_x, int b_y) : 
		x(float(b_x)), 
		y(float(b_y)) 
	{};

	//////////////////////////////////////////
	// COPY
	Vector2f(Vector2f& const other)
	{
		Vector2f(other.x, other.y);
	};
	Vector2f operator=(Vector2f& const other)
	{
		Vector2f(other.x, other.y);
	};
	//////////////////////////////////////////
	
	//////////////////////////////////////////
	// MOVE
	Vector2f(Vector2f&& other)
	{
		Vector2f(other);

		other.~Vector2f();
	};
	Vector2f operator=(Vector2f&& other)
	{
		Vector2f(other);

		other.~Vector2f();
	};
	///////////////////////////////////////////
	
	~Vector2f() = default;

	///////////////
	// OPERATORS //
	///////////////

	Vector2f operator+(Vector2f other)
	{
		return Vector2f(
			x + other.x, 
			y + other.y
		);
	};
	
	Vector2f operator+=(Vector2f other)
	{
		x += other.x;
		y += other.y;

		return *this;
	};

	Vector2f operator-(Vector2f other)
	{
		return Vector2f(
			x - other.x, 
			y - other.y
		);
	};


	Vector2f operator-=(Vector2f other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	};


	Vector2f operator*(float multiplier)
	{
		return Vector2f(
			x * multiplier, 
			y * multiplier
		);
	};


	Vector2f operator*=(float multiplier)
	{
		x *= multiplier;
		y *= multiplier;

		return *this;
	};


	Vector2f operator/(float divider)
	{
		return Vector2f(
			x / divider, 
			y / divider
		);
	};


	Vector2f operator/=(float divider)
	{
		x /= divider;
		y /= divider;

		return *this;
	};

	bool operator<(Vector2f other)
	{
		if (x > other.x and y > other.y) return true;
		return false;
	};

	bool operator<=(Vector2f other)
	{
		if (x >= other.x and y >= other.y) return true;
		return false;
	};

	bool operator>(Vector2f other)
	{
		if (x < other.x and y < other.y) return true;
		return false;
	};

	bool operator>=(Vector2f other)
	{
		if (x <= other.x and y <= other.y) return true;
		return false;
	};
};

struct Vector3f
{
	float x, y, z;

	Vector3f() : 
		x(0.0f), 
		y(0.0f), 
		z(0.0f) 
	{};

	Vector3f(float b_x, float b_y, float b_z) : 
		x(b_x), 
		y(b_y), 
		z(b_z) 
	{};
	Vector3f(int b_x, int b_y, float b_z) : 
		x(float(b_x)), 
		y(float(b_y)), 
		z(float(b_z)) 
	{};

	//////////////////////////////////////////
	// COPY
	Vector3f(Vector3f& const other)
	{
		Vector3f(other.x, other.y, other.z);
	};
	Vector3f operator=(Vector3f& const other)
	{
		Vector3f(other.x, other.y, other.z);
	};
	//////////////////////////////////////////

	//////////////////////////////////////////
	// MOVE
	Vector3f(Vector3f&& other)
	{
		Vector3f(other);

		other.~Vector3f();
	};
	Vector3f operator=(Vector3f&& other)
	{
		Vector3f(other);

		other.~Vector3f();
	};
	///////////////////////////////////////////

	~Vector3f() = default;

	///////////////
	// OPERATORS //
	///////////////

	Vector3f operator+(Vector3f other)
	{
		return Vector3f(
			x + other.x, 
			y + other.y, 
			z + other.z
		);
	};

	Vector3f operator+=(Vector3f other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	};

	Vector3f operator-(Vector3f other)
	{
		return Vector3f(
			x - other.x, 
			y - other.y, 
			z - other.z
		);
	};


	Vector3f operator-=(Vector3f other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	};


	Vector3f operator*(float multiplier)
	{
		return Vector3f(
			x * multiplier, 
			y * multiplier, 
			z * multiplier
		);
	};


	Vector3f operator*=(float multiplier)
	{
		x *= multiplier;
		y *= multiplier;
		z *= multiplier;

		return *this;
	};


	Vector3f operator/(float divider)
	{
		return Vector3f(
			x / divider, 
			y / divider, 
			z / divider
		);
	};


	Vector3f operator/=(float divider)
	{
		x /= divider;
		y /= divider;
		z /= divider;

		return *this;
	};
};

struct Vector4f
{
	float x, y, z, w;

	Vector4f() : 
		x(0.0f), 
		y(0.0f), 
		z(0.0f), 
		w(0.0f) 
	{};

	Vector4f(float b_x, float b_y, float b_z, float b_w) : 
		x(b_x), 
		y(b_y), 
		z(b_z), 
		w(b_w) 
	{};
	Vector4f(int b_x, int b_y, float b_z, float b_w) : 
		x(float(b_x)), 
		y(float(b_y)),
		z(float(b_z)),
		w(float(b_w)) 
	{};

	//////////////////////////////////////////
	// COPY
	Vector4f(Vector4f& const other)
	{
		Vector4f(other.x, other.y, other.z, other.w);
	};
	Vector4f operator=(Vector4f& const other)
	{
		Vector4f(other.x, other.y, other.z, other.w);
	};
	//////////////////////////////////////////

	//////////////////////////////////////////
	// MOVE
	Vector4f(Vector4f&& other)
	{
		Vector4f(other);

		other.~Vector4f();
	};
	Vector4f operator=(Vector4f&& other)
	{
		Vector4f(other);

		other.~Vector4f();
	};
	///////////////////////////////////////////

	~Vector4f() = default;

	///////////////
	// OPERATORS //
	///////////////

	Vector4f operator+(Vector4f other)
	{
		return Vector4f(
			x + other.x,
			y + other.y,
			z + other.z,
			w + other.w
		);
	};

	Vector4f operator+=(Vector4f other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	};

	Vector4f operator-(Vector4f other)
	{
		return Vector4f(
			x - other.x, 
			y - other.y, 
			z - other.z, 
			w - other.w
		);
	};


	Vector4f operator-=(Vector4f other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	};


	Vector4f operator*(float multiplier)
	{
		return Vector4f(x * multiplier, y * multiplier, z * multiplier, w * multiplier);
	};


	Vector4f operator*=(float multiplier)
	{
		x *= multiplier;
		y *= multiplier;
		z *= multiplier;
		w *= multiplier;

		return *this;
	};


	Vector4f operator/(float divider)
	{
		return Vector4f(
			x / divider, 
			y / divider, 
			z / divider, 
			w / divider
		);
	};


	Vector4f operator/=(float divider)
	{
		x /= divider;
		y /= divider;
		z /= divider;
		w /= divider;

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
	Color(unsigned int b_r, unsigned int b_g, unsigned int b_b, unsigned int b_a) :
		r(b_r),
		g(b_g),
		b(b_b),
		a(b_a)
	{};

	///////////////////////////////////////////
	// COPY
	Color(Color& const other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
	}
	Color operator=(Color& const other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
	}
	///////////////////////////////////////////

	///////////////////////////////////////////
	// MOVE
	Color(Color&& other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;

		other.~Color();
	}
	Color operator=(Color&& other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;

		other.~Color();
	}
	///////////////////////////////////////////

	~Color() = default;

};

constexpr struct {
	Color RED     { 255, 0, 0, 255 }; // 255 0 0
	Color GREEN   { 0, 255, 0, 255 }; // 0 255 0
	Color BLUE    { 0, 0, 255, 255 }; // 0 0 255

	Color YELLOW  { 255, 255, 0, 255 }; // 255 255 0
	Color CYAN    { 0, 255, 255, 255 }; // 0 255 255
	Color MAGENTA { 255, 0, 255, 255 }; // 255 0 255

	Color WHITE   { 255, 255, 255, 255 }; // 255 255 255
	Color BLACK   { 0, 0, 0, 255 }; // 0 0 0
	Color CLEAR   { 0, 0, 0, 0 }; // 0 0 0 0
} COLORS;