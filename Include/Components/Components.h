#pragma once
#include "Geometry/Precision.h"
#include "Geometry/Vector3.h"

struct Component
{
	int GameObjectID = -1;
	bool Active = true;
};

struct PhysicsMaterial :Component
{
	FP restitution = 1;
	FP friction = 0;
};

struct Particle_position
{
	Vector3 pos = 0;
};

struct Particle_size
{
	float size = 1;
};



struct Particle :Component
{
	Vector3 position = 0;
	FP radius = 1;
	FP inverse_mass = 1;
	Vector3 velocity = 0;
	Vector3 acceleration = 0;
	PhysicsMaterial* material = nullptr;
};









