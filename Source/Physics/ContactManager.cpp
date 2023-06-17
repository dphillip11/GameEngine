#include "PCH/pch.h"
#include "Physics/ContactManager.h"

void ContactManager::RegisterContact(ParticleContact& contact)
{
	contact.collisionSpeed = (contact.particleB->velocity - contact.particleA->velocity).Dot(contact.collisionNormal);
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
void ContactManager::AdjustPositions(const ParticleContact& contact)
{
	if (contact.penetration <= 0) return;
	FP totalInverseMass = contact.particleA->inverse_mass + contact.particleB->inverse_mass;
	// both particles have infinite mass
	if (totalInverseMass <= 0) return;

	Vector3  depthMass = contact.collisionNormal * (contact.penetration / totalInverseMass);

	//infinite mass is handled automatically here because it will have zero inverso mass
	contact.particleA->position += depthMass * contact.particleA->inverse_mass;
	contact.particleB->position -= depthMass * contact.particleB->inverse_mass;
}



void ContactManager::AdjustVelocities(const ParticleContact& contact)
{
	// Check if the particles are moving apart
	if (contact.collisionSpeed < 0)
		return;
	//check for infinite mass
	if (contact.particleA->inverse_mass == 0 && contact.particleB->inverse_mass == 0)
		return;

	// Calculate the restitution coefficient
	FP restitutionA = contact.particleA->material ? contact.particleA->material->restitution : 1;
	FP restitutionB = contact.particleB->material ? contact.particleB->material->restitution : 1;
	FP restitution = (restitutionA + restitutionB) / 2;

	FP seperatingSpeed = -contact.collisionSpeed * restitution;
	FP deltaSpeed = seperatingSpeed - contact.collisionSpeed;

	FP totalInverseMass = contact.particleA->inverse_mass + contact.particleB->inverse_mass;
	//impulse directed away from A
	Vector3 impulseMass = contact.collisionNormal * (deltaSpeed / totalInverseMass);

	contact.particleA->velocity -= impulseMass * contact.particleA->inverse_mass;
	contact.particleB->velocity += impulseMass * contact.particleB->inverse_mass;
}