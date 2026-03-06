#ifndef FOUNDRY_TRANSFORM2D__H_
#define FOUNDRY_TRANSFORM2D__H_

#include "SimpleContainers/Vector.hpp"

/// <summary>
/// Describes a 2D element in a 2D space world.
/// Handles positionning, scaling, rotation and statism (parameters locked or unlocked).
/// </summary>
class Transform2D
{
public:
	enum class Axis : char
	{
		X = 'x',
		Y = 'y',
		Z = 'z'
	};

	Transform2D(
		float _x = 0.0f, float _y = 0.0f,
		float _scaleX = 1.0f, float _scaleY = 1.0f,
		float _theta = 0.0f,
		bool _statism = false
	);
	~Transform2D();

	Transform2D(Transform2D const& other);
	Transform2D& operator=(Transform2D const& other);

	Transform2D(Transform2D&& other) noexcept;
	Transform2D& operator=(Transform2D&& other) noexcept;


	Transform2D  operator*(Transform2D const& other) const;
	Transform2D& operator*=(Transform2D const& other);

	Transform2D  operator+(Transform2D const& other) const;
	Transform2D& operator+=(Transform2D const& other);
	
	Transform2D  operator-(Transform2D const& other) const;
	Transform2D& operator-=(Transform2D const& other);

	Transform2D  operator/(Transform2D const& other) const;
	Transform2D& operator/=(Transform2D const& other);


	void		SetShearing(glm::vec2 _shear);
	void		SetShearing(float _u, float _v);
	void		SetShearingOnAxis(Axis _axis, float _shear);
	Vector2f	GetShearing() const;

	void		SetMirroringOnAxis(Axis _axis);

	void		SetScale(Vector2f _scale);
	void		SetScale(float _width, float _height);
	Vector2f	GetScale() const;

	void		SetRotation(float _rotX, float _rotY);
	Vector2f	GetRotation() const;

	void		SetPosition(Vector2f _pos);
	void		SetPosition(float _x, float _y);
	Vector2f	GetPosition() const;

	glm::mat3	GetTransformationMatrix() const;
	void		SetTransformationMatrix();

	void		SetStatism(bool _statism);
	bool		IsStatic() const;

	void		Update();

private:
	bool m_isStatic;
	bool m_isDirty;

	glm::vec3 m_scale;
	glm::vec3 m_shear;
	glm::vec3 m_rotation;
	glm::vec3 m_position;
	
	glm::mat3 m_transformationMatrix;
};


#endif