#pragma once
#include "Geometry/Precision.h"
#include "Geometry/Vector3.h"


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










