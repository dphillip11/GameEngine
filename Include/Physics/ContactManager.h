#pragma once
#include "Physics/CollisionContacts.h"
#include <queue>

class ContactManager
{
private:
	//particle contact functions
	void SolveParticleContact(ParticleContact& contact);
	void AdjustPositions(ParticleContact& contact);
	void AdjustVelocities(ParticleContact& contact);

	// Define a comparison function for the priority queue
	struct CompareParticleContact {
		bool operator()(const ParticleContact& contact1, const ParticleContact& contact2) {
			return contact1.collisionSpeed > contact2.collisionSpeed;
		}
	};

public:
	// Create a priority queue to store ParticleContact objects
	std::priority_queue<ParticleContact, std::vector<ParticleContact>, CompareParticleContact> particleContacts;

	void RegisterContact(ParticleContact& contact);
	void ResolveContacts();
	auto& GetParticleContacts() { return particleContacts; }
};
