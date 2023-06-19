#pragma once
#include "Components/Components.h"
#include "Physics/ContactManager.h"
#include "Scene/scene.h"

class CollisionDetection
{
private:
	Scene& m_scene;
	ContactManager m_contact_manager;
public:
	const auto& GetContacts()
	{
		return m_contact_manager.particleContacts;
	}
	CollisionDetection(Scene& scene) :m_scene(scene), m_contact_manager(ContactManager(m_scene)) {}
	void CheckParticleCollisions();
	void CheckParticleCollision(Particle_Position& A_pos, Particle_Position& B_pos, Particle_Radius& A_radius, Particle_Radius& B_radius, int ID_A, int ID_B);
	void Update();
};

