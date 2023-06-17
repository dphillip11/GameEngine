#include "PCH/pch.h"
#include "Physics/CollisionDetection.h"

void CollisionDetection::Update()
{
	CheckCollisions();
	m_contact_manager.ResolveContacts();
}

void CollisionDetection::CheckCollisions()
{
	for (size_t i = 0; i < m_particle_registry.size(); ++i)
	{
		Particle& particleA = m_particle_registry[i];

		for (size_t j = i + 1; j < m_particle_registry.size(); ++j)
		{
			Particle& particleB = m_particle_registry[j];

			CheckCollision(particleA, particleB);
		}
	}
}

void CollisionDetection::CheckCollision(Particle& A, Particle& B)
{
	Vector3 CollisionVector = (A.position - B.position);
	FP distance = CollisionVector.Length();
	FP sumOfRadii = A.radius + B.radius;
	if (distance > sumOfRadii)
		return;
	ParticleContact contact;
	contact.collisionNormal = CollisionVector.Normalise();
	contact.particleA = &A;
	contact.particleB = &B;
	contact.penetration = distance - sumOfRadii;
	m_contact_manager.RegisterContact(contact);
}