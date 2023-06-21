#include "PCH/pch.h"
#include "Physics/CollisionDetection.h"
#include "Scene/scene.h"



void CollisionDetection::Update()
{
	CheckParticleCollisions();
	m_contact_manager->ResolveContacts();
}

CollisionDetection::CollisionDetection()
{
	m_contact_manager = std::make_unique<ContactManager>();
}

void CollisionDetection::CheckParticleCollisions()
{
	auto& m_scene = *Scene::Get();
	auto& positions = m_scene.componentRegistry->GetComponentsByType<Particle_Position>();
	auto& radii = m_scene.componentRegistry->GetComponentsByType<Particle_Radius>();
	auto& IDs = m_scene.componentRegistry->GetComponentsByType<Particle_ID>();

	auto number = positions.size();
	if (number != radii.size())
		throw(std::runtime_error("CollisionDetection:: particle vector size mismatch"));
	for (size_t i = 0; i < number; ++i)
	{
		for (size_t j = i + 1; j < number; ++j)
		{

			CheckParticleCollision(positions[i], positions[j], radii[i], radii[j], IDs[i].value, IDs[j].value);
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
	contact.particleA = Scene::Get()->entityRegistry->GetRef(ID_A);
	contact.particleB = Scene::Get()->entityRegistry->GetRef(ID_B);
	contact.penetration = distance - sumOfRadii;
	m_contact_manager->RegisterContact(contact);
}