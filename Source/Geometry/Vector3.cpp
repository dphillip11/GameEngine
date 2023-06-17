#include "Geometry/Vector3.h"
#include <cmath>

Vector3::Vector3(FP X, FP Y, FP Z)
{
	x = X;
	y = Y;
	z = Z;
}

Vector3::Vector3(FP val)
{
	x = val;
	y = val;
	z = val;
}

Vector3& Vector3::operator=(const Vector3& other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}
	return *this;
}

Vector3& Vector3::operator=(FP scalar)
{
	x = scalar;
	y = scalar;
	z = scalar;

	return *this;
}

bool Vector3::operator==(const Vector3& other) const {
	return std::abs(x - other.x) < std::numeric_limits<float>::epsilon() &&
		std::abs(y - other.y) < std::numeric_limits<float>::epsilon() &&
		std::abs(z - other.z) < std::numeric_limits<float>::epsilon();
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	Vector3 result(x + other.x, y + other.y, z + other.z);
	return result;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	Vector3 result(x - other.x, y - other.y, z - other.z);
	return result;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3 Vector3::operator*(const FP& scale) const
{
	Vector3 result(x * scale, y * scale, z * scale);
	return result;
}

Vector3& Vector3::operator*=(const FP& scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
	return *this;
}

Vector3 Vector3::operator/(const FP& scale) const
{
	Vector3 result(x / scale, y / scale, z / scale);
	return result;
}

Vector3& Vector3::operator/=(const FP& scale)
{
	x /= scale;
	y /= scale;
	z /= scale;
	return *this;
}

FP Vector3::Length() const
{
	return sqrt(x * x + y * y + z * z);
}

FP Vector3::LengthSquared() const
{
	return x * x + y * y + z * z;
}

Vector3 Vector3::Normalise() const
{
	FP length = Length();
	if (length > 0)
	{
		return (*this * (1 / length));
	}
	else
	{
		return Vector3(0);
	}

}

FP Vector3::Dot(const Vector3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::Cross(const Vector3& other) const
{
	Vector3 result(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	);
	return result;
}
