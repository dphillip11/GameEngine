#include "PCH/pch.h"
#include "Physics/ContactManager.h"
#include "Scene/scene.h"
#include "Entity/entity.h"

void ContactManager::RegisterContact(ParticleContact& contact)
{
	auto& velocityA = contact.particleA.getComponent<Particle_Velocity>();
	auto& velocityB = contact.particleB.getComponent<Particle_Velocity>();
	contact.collisionSpeed = (velocityB.value - velocityA.value).Dot(contact.collisionNormal);
	particleContacts.push(contact);
}

void ContactManager::ResolveContacts()
{
	while (!particleContacts.empty())
	{
		ParticleContact contact = particleContacts.top();
		particleContacts.pop();
		SolveParticleContact(contact);
	}
}

//particle contact functions
void ContactManager::SolveParticleContact(ParticleContact& contact)
{
	AdjustPositions(contact);
	AdjustVelocities(contact);
}
void ContactManager::AdjustPositions(ParticleContact& contact)
{
	auto& m_scene = *Scene::Get();
	auto& inv_mass_A = contact.particleA.getComponent<Particle_InverseMass>().value;
	auto& inv_mass_B = contact.particleB.getComponent<Particle_InverseMass>().value;
	if (contact.penetration <= 0) return;
	FP totalInverseMass = inv_mass_A + inv_mass_B;
	// both particles have infinite mass
	if (totalInverseMass <= 0) return;

	Vector3  depthMass = contact.collisionNormal * (contact.penetration / totalInverseMass);

	//infinite mass is handled automatically here because it will have zero inverso mass
	contact.particleA.getComponent<Particle_Position>().value += depthMass * inv_mass_A;
	contact.particleB.getComponent<Particle_Position>().value -= depthMass * inv_mass_B;
}



void ContactManager::AdjustVelocities(ParticleContact& contact)
{
	// Check if the particles are moving apart
	if (contact.collisionSpeed < 0)
		return;
	//check for infinite mass
	auto& inv_mass_A = contact.particleA.getComponent<Particle_InverseMass>().value;
	auto& inv_mass_B = contact.particleB.getComponent<Particle_InverseMass>().value;
	if (inv_mass_A == 0 && inv_mass_B == 0)
		return;

	// Calculate the restitution coefficient
	auto& restitutionA = contact.particleA.getComponent<Particle_Restitution>().value;
	auto& restitutionB = contact.particleB.getComponent<Particle_Restitution>().value;
	FP restitution = (restitutionA + restitutionB) / 2;

	FP seperatingSpeed = -contact.collisionSpeed * restitution;
	FP deltaSpeed = seperatingSpeed - contact.collisionSpeed;

	FP totalInverseMass = inv_mass_A + inv_mass_B;
	//impulse directed away from A
	Vector3 impulseMass = contact.collisionNormal * (deltaSpeed / totalInverseMass);

	auto& velocity_A = contact.particleA.getComponent<Particle_Velocity>().value;
	auto& velocity_B = contact.particleB.getComponent<Particle_Velocity>().value;
	velocity_A -= impulseMass * inv_mass_A;
	velocity_B += impulseMass * inv_mass_B;
}