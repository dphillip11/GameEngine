#include "Precision.h"
#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
public:
	FP x = 0;
	FP y = 0;
	FP z = 0;

	Vector3() = default;
	Vector3(FP X, FP Y, FP Z);
	Vector3(FP val);

	Vector3& operator=(const Vector3& other);
	Vector3& operator=(FP scalar);
	bool operator==(const Vector3& other) const;

	Vector3 operator+(const Vector3& other) const;
	Vector3& operator+=(const Vector3& other);

	Vector3 operator-(const Vector3& other) const;
	Vector3& operator-=(const Vector3& other);

	Vector3 operator*(const FP& scale) const;
	Vector3& operator*=(const FP& scale);

	Vector3 operator/(const FP& scale) const;
	Vector3& operator/=(const FP& scale);

	FP Length() const;

	FP LengthSquared() const;

	Vector3 Normalise() const;

	FP Dot(const Vector3& other) const;

	Vector3 Cross(const Vector3& other) const;

};

#endif // VECTOR3_H
