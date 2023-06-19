#pragma once
#include "Components/Components.h"

struct ParticleContact
{
	int particleA_id;
	int particleB_id;
	FP penetration;
	//direction of collision towards particle A
	Vector3 collisionNormal;
	//relative speed along collision normal, positive if going towards each other
	FP collisionSpeed;
};

