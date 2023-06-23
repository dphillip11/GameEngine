#pragma once
#include "Geometry/Precision.h"
#include "Geometry/Vector3.h"
#include <cstring>

////equality operator, TODO: consider this as a base class? 
//struct Component {
//	// ... other members and functions ...
//
//	// Declare the operator== inside the struct
//	bool operator==(const Component& other) const {
//		return (std::memcmp(this, &other, sizeof(Component)) == 0);
//	}
//};
//
//// Define the operator== outside the struct
//bool operator==(const Component& lhs, const Component& rhs) {
//	return (std::memcmp(&lhs, &rhs, sizeof(Component)) == 0);
//}

struct Particle_Friction
{
	FP value = 0;
};

struct Particle_Position
{
	Vector3 value = 0;
};

struct Particle_Radius
{
	FP value = 1;
};

struct Particle_InverseMass
{
	FP value = 1;
};

struct Particle_Velocity
{
	Vector3 value = 0;
};

struct Particle_Acceleration
{
	Vector3 value = 0;
};

struct Particle_Restitution
{
	FP value = 1;
};

struct Particle_ID
{
	unsigned int value = -1;
};

struct Line_Coordinates
{
	Vector3 A;
	Vector3 B;
};

struct Line_Color
{
	//color for each vertex
	Vector3 A;
	Vector3 B;
};










