#pragma once
#include "Physics/CollisionContacts.h"
#include <queue>
#include "Scene/scene.h"

// Define a comparison function for the priority queue
struct CompareParticleContact {
	bool operator()(const ParticleContact& contact1, const ParticleContact& contact2) {
		return contact1.collisionSpeed > contact2.collisionSpeed;
	}
};

// Define the ParticleContactQueue type alias
using ParticleContactQueue = std::priority_queue<ParticleContact, std::vector<ParticleContact>, CompareParticleContact>;

class ContactManager
{
private:
	//particle contact functions
	void SolveParticleContact(ParticleContact& contact);
	void AdjustPositions(const ParticleContact& contact);
	void AdjustVelocities(const ParticleContact& contact);

	// Create a priority queue to store ParticleContact objects
	ParticleContactQueue particleContacts;

public:
	void RegisterContact(ParticleContact&);
	void ResolveContacts();
	ParticleContactQueue& GetParticleContacts() { return particleContacts; }
};
