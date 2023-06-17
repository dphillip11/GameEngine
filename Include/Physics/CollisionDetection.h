#pragma once
#include "Components/Components.h"
#include "Physics/ContactManager.h"

class CollisionDetection
{
private:
	std::vector<Particle>& m_particle_registry;
	ContactManager m_contact_manager;
public:
	const auto& GetContacts()
	{
		return m_contact_manager.particleContacts;
	}
	CollisionDetection(std::vector<Particle>& particle_registry) :m_particle_registry(particle_registry) {}
	void CheckCollisions();
	void CheckCollision(Particle& A, Particle& B);
	void Update();
};

