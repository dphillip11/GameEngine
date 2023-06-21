#pragma once

#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "Components/Components.h"
#include <memory>
#include "Physics/ContactManager.h"

class CollisionDetection
{
private:


public:

	std::unique_ptr<ContactManager> m_contact_manager;
	CollisionDetection();
	void CheckParticleCollisions();
	void CheckParticleCollision(
		Particle_Position& A_pos,
		Particle_Position& B_pos,
		Particle_Radius& A_radius,
		Particle_Radius& B_radius,
		int ID_A,
		int ID_B
	);
	void Update();
};

#endif // COLLISIONDETECTION_H
