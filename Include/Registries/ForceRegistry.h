#pragma once
#include "Components/Components.h"
#include "Physics/ForceGenerator.h"
#include <vector>

// Class to hold the force generator and the particle it applies to
class ForceRegistration {
public:
	ForceGenerator* generator;
	Particle* particle;

	ForceRegistration(ForceGenerator* gen, Particle* particle)
		: generator(gen), particle(particle) {}
};

// Force registry class
class ForceRegistry {
private:
	std::vector<ForceRegistration> registrations;

public:
	// Register a force generator for a particle
	void AddForceGenerator(ForceGenerator* generator, Particle* particle) {
		registrations.emplace_back(generator, particle);
	}

	// Remove a force generator for a particle
	void RemoveForceGenerator(ForceGenerator* generator, Particle* particle) {
		for (auto it = registrations.begin(); it != registrations.end(); ++it) {
			if (it->generator == generator && it->particle == particle) {
				registrations.erase(it);
				break;
			}
		}
	}

	// Apply forces to all registered particles
	void UpdateForces(double dt) {
		for (auto& registration : registrations) {
			registration.generator->ApplyForce(registration.particle, dt);
		}
		for (int i = 0; i < registrations.size(); i++)
		{
			std::cout << registrations[i].particle->radius << std::endl;
		}
	}

	void Clear() {
		registrations.clear();
	}
};

