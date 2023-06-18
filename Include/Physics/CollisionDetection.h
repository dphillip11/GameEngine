#pragma once
#include "Components/Components.h"
#include "Physics/ContactManager.h"

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
	CollisionDetection(Scene& scene) :m_scene(scene) {}
	void CheckCollisions();
	void CheckCollision(Particle& A, Particle& B);
	void Update();
};

