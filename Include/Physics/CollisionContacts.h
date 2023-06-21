#pragma once
#include "Components/Components.h"
#include "entity/entity.h"

struct ParticleContact
{
	EntityRef particleA;
	EntityRef particleB;
	FP penetration;
	//direction of collision towards particle A
	Vector3 collisionNormal;
	//relative speed along collision normal, positive if going towards each other
	FP collisionSpeed;
};

