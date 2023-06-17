#pragma once
#include "Registries/ComponentRegistry.h"
#include "Registries/ForceRegistry.h"
#include "Managers/ParticleManager.h"
#include "Physics/CollisionDetection.h"
#include "Rendering/ParticleRenderer.h"
#include <memory>

class Scene
{
public:
	std::unique_ptr<ComponentRegistry> componentRegistry = nullptr;
	std::unique_ptr <ParticleManager> particleManager = nullptr;
	std::unique_ptr <ForceRegistry> forceRegistry = nullptr;
	std::unique_ptr <CollisionDetection> collisionDetection = nullptr;
	std::unique_ptr <ParticleRenderer> particleRenderer = nullptr;


	Scene() {
		componentRegistry = std::make_unique<ComponentRegistry>();
		particleManager = std::make_unique<ParticleManager>(componentRegistry->GetComponentVector<Particle>());
		forceRegistry = std::make_unique<ForceRegistry>();
		collisionDetection = std::make_unique<CollisionDetection>(componentRegistry->GetComponentVector<Particle>());
		particleRenderer = std::make_unique <ParticleRenderer>(componentRegistry->GetComponentVector<Particle>());
	}

	void Update(FP_LONG dt)
	{
		collisionDetection->Update();
		forceRegistry->UpdateForces(dt);
		particleManager->UpdateAllParticles(dt);
	}

};

