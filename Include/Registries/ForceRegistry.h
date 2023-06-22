#pragma once
#include "Components/Components.h"
#include "Physics/ForceGenerator.h"
#include <vector>

class ForceRegistry {
private:
	struct ForceRegistration {
		std::unique_ptr<ForceGenerator> generator;
		EntityRef entity;

		ForceRegistration(std::unique_ptr<ForceGenerator>&& gen, EntityRef newEntity)
			: generator(std::move(gen)), entity(newEntity) {}
	};

	std::vector<ForceRegistration> registrations;

public:
	// Register a force generator for a particle
	template <typename T>
	T* AddForceGenerator(T& generator, EntityRef entity) {
		auto uniqueGenerator = std::make_unique<T>(generator);
		registrations.emplace_back(std::move(uniqueGenerator), entity);
		return static_cast<T*>(&(*registrations.back().generator));
	}

	// Remove a force generator for a particle
	void RemoveForceGenerator(ForceGenerator* generator, EntityRef entity) {
		auto it = std::find_if(registrations.begin(), registrations.end(),
			[&](const ForceRegistration& reg) { return reg.generator.get() == generator && reg.entity.m_entityID == entity.m_entityID; });
		if (it != registrations.end()) {
			registrations.erase(it);
		}
	}

	// Apply forces to all registered particles
	void UpdateForces(FP_LONG dt) {
		for (auto& registration : registrations) {
			registration.generator->ApplyForce(registration.entity, dt);
		}
	}

	void Clear() {
		registrations.clear();
	}
};
