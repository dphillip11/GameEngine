#pragma once
#include "Components/Components.h"
#include "Physics/ForceGenerator.h"
#include <vector>

// Class to hold the force generator and the particle it applies to
class ForceRegistration {
public:
	ForceGenerator* generator;
	EntityRef entity;

	ForceRegistration(ForceGenerator* gen, EntityRef new_entity)
		: generator(gen), entity(new_entity) {}
};

// Force registry class
class ForceRegistry {
private:
	std::vector<ForceRegistration> registrations;

public:
	// Register a force generator for a particle
	void AddForceGenerator(ForceGenerator* generator, EntityRef entity) {
		registrations.emplace_back(generator, entity);
	}

	// Remove a force generator for a particle
	void RemoveForceGenerator(ForceGenerator* generator, EntityRef entity) {
		for (auto it = registrations.begin(); it != registrations.end(); ++it) {
			if (it->generator == generator && it->entity.m_entityID == entity.m_entityID) {
				registrations.erase(it);
				break;
			}
		}
	}

	// Apply forces to all registered particles
	void UpdateForces(double dt) {
		for (auto& registration : registrations) {
			registration.generator->ApplyForce(registration.entity, dt);
		}
	}

	void Clear() {
		registrations.clear();
	}
};

