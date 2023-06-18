#pragma once
#include "Entity/Entity.h"
#include "Registries/ForceRegistry.h"
#include "Managers/ParticleManager.h"
#include "Physics/CollisionDetection.h"
#include "Rendering/ParticleRenderer.h"
#include <memory>

class Scene
{
public:
	std::unique_ptr<ComponentRegistry> componentRegistry = nullptr;
	std::unique_ptr<EntityRegistry> entityRegistry = nullptr;
	std::unique_ptr <ParticleManager> particleManager = nullptr;
	std::unique_ptr <ForceRegistry> forceRegistry = nullptr;
	std::unique_ptr <CollisionDetection> collisionDetection = nullptr;
	std::unique_ptr <ParticleRenderer> particleRenderer = nullptr;


	Scene() {
		componentRegistry = std::make_unique<ComponentRegistry>();
		entityRegistry = std::make_unique<EntityRegistry>();
		forceRegistry = std::make_unique<ForceRegistry>();
		particleManager = std::make_unique<ParticleManager>(*this);
		collisionDetection = std::make_unique<CollisionDetection>(*this);
		particleRenderer = std::make_unique <ParticleRenderer>(*this);
	}

	void Update(FP_LONG dt)
	{
		collisionDetection->Update();
		forceRegistry->UpdateForces(dt);
		particleManager->UpdateAllParticles(dt);
	}

};

