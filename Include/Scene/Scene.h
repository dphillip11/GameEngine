#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "Entity/Entity.h"
#include "Registries/ForceRegistry.h"
#include "Managers/ParticleManager.h"
#include "Physics/CollisionDetection.h"
#include "Rendering/ParticleRenderer.h"
#include "Rendering/LineRenderer.h"
#include "Scene/CameraControl.h"
#include "Rendering/Camera.h"
#include <memory>


class Scene
{
private:
	static Scene* current;
	std::unique_ptr<CameraControl> cameraControl;

public:
	static void SetCurrent(Scene* scene)
	{
		if (scene == nullptr)
			throw(std::runtime_error("Scene: invalid scene pointer"));
		current = scene;
	}

	static Scene* Get()
	{
		if (!current)
			throw(std::runtime_error("Scene: invalid scene pointer"));
		return current;
	}

	std::unique_ptr<ComponentRegistry> componentRegistry = nullptr;
	std::unique_ptr<EntityRegistry> entityRegistry = nullptr;
	std::unique_ptr<ParticleManager> particleManager = nullptr;
	std::unique_ptr<ForceRegistry> forceRegistry = nullptr;
	std::unique_ptr<CollisionDetection> collisionDetection = nullptr;
	std::unique_ptr<ParticleRenderer> particleRenderer = nullptr;
	std::unique_ptr<LineRenderer> lineRenderer = nullptr;
	Camera camera{ glm::vec3(0),glm::vec3(0,0,-15) };

	Scene()
	{
		current = this;
		componentRegistry = std::make_unique<ComponentRegistry>();
		entityRegistry = std::make_unique<EntityRegistry>();
		forceRegistry = std::make_unique<ForceRegistry>();
		particleManager = std::make_unique<ParticleManager>();
		collisionDetection = std::make_unique<CollisionDetection>();
		particleRenderer = std::make_unique<ParticleRenderer>();
		lineRenderer = std::make_unique<LineRenderer>();
		cameraControl = std::make_unique<CameraControl>(camera);
	}

	void Update(FP_LONG dt)
	{

		if (collisionDetection)
		{
			collisionDetection->Update();
		}
		if (cameraControl)
			cameraControl->ProcessInput(dt);
		if (forceRegistry)
		{
			forceRegistry->UpdateForces(dt);
		}
		if (particleManager)
		{
			particleManager->UpdateAllParticles(dt);
		}
	}

	void Render()
	{
		particleRenderer->DrawParticles();
		lineRenderer->DrawLines();
	}

};

#endif // SCENE_H
