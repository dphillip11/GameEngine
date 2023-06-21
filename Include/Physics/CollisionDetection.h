#pragma once

#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H
#include "Components/Components.h"
#include "Physics/ContactManager.h"

class CollisionDetection
{
private:
	ContactManager m_contact_manager;
public:
	CollisionDetection() = default;
	ParticleContactQueue& GetContacts()
	{
		return m_contact_manager.GetParticleContacts();
	}
	void CheckParticleCollisions();
	void CheckParticleCollision(Particle_Position& A_pos, Particle_Position& B_pos, Particle_Radius& A_radius, Particle_Radius& B_radius, int ID_A, int ID_B);
	void Update();
};
#endif //COLLISIONDETECTION_H

