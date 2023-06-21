#include "PCH/pch.h"
#include "Physics/CollisionDetection.h"
#include "Scene/scene.h"


void CollisionDetection::Update()
{
	CheckParticleCollisions();
	m_contact_manager.ResolveContacts();
}

void CollisionDetection::CheckParticleCollisions()
{
	auto& m_scene = *Scene::Get();
	auto& positions = m_scene.componentRegistry->GetComponentsByType<Particle_Position>();
	auto& radii = m_scene.componentRegistry->GetComponentsByType<Particle_Radius>();

	auto number = positions.size();
	if (number != radii.size())
		throw(std::runtime_error("CollisionDetection:: particle vector size mismatch"));
	for (size_t i = 0; i < number; ++i)
	{
		for (size_t j = i + 1; j < number; ++j)
		{

			CheckParticleCollision(positions[i], positions[j], radii[i], radii[j], i, j);
		}
	}
}

void CollisionDetection::CheckParticleCollision(Particle_Position& A_pos, Particle_Position& B_pos, Particle_Radius& A_radius, Particle_Radius& B_radius, int ID_A, int ID_B)
{
	Vector3 CollisionVector = (A_pos.value - B_pos.value);
	FP distance = CollisionVector.Length();
	FP sumOfRadii = A_radius.value + B_radius.value;
	if (distance > sumOfRadii)
		return;
	ParticleContact contact;
	contact.collisionNormal = CollisionVector.Normalise();
	contact.particleA_id = ID_A;
	contact.particleB_id = ID_B;
	contact.penetration = distance - sumOfRadii;
	m_contact_manager.RegisterContact(contact);
}