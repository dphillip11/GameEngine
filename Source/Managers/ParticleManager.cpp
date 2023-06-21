#include "PCH/pch.h"
#include "Managers/ParticleManager.h"
#include "Registries/ComponentRegistry.h"
#include "Entity/entity.h"
#include "Scene/scene.h"

EntityRef ParticleManager::NewParticle()
{
	auto& m_scene = *Scene::Get();
	EntityRef entity_ref = m_scene.entityRegistry->CreateEntity(*m_scene.componentRegistry);
	auto& entity = entity_ref.getEntity();
	entity.EmplaceComponent<Particle_Position>();
	entity.EmplaceComponent<Particle_Radius>();
	entity.EmplaceComponent<Particle_InverseMass>();
	entity.EmplaceComponent<Particle_Velocity>();
	entity.EmplaceComponent<Particle_Acceleration>();
	entity.EmplaceComponent<Particle_Restitution>();
	entity.EmplaceComponent<Particle_Friction>();
	entity.EmplaceComponent<Particle_ID>(entity_ref.m_entityID);
	return entity_ref;
}

// updates velocity based on acceleration and time
void ParticleManager::IntegrateAcceleration(FP_LONG dt, Particle_Velocity& velocity, Particle_Acceleration& acceleration)
{
	velocity.value += (acceleration.value * dt);
	acceleration.value = Vector3(0);
}
// update position based on velocity and time
void ParticleManager::IntegrateVelocity(FP_LONG dt, Particle_Position& position, Particle_Velocity& velocity)
{
	position.value += (velocity.value * dt);
}

// updates particle positions based on position, velocityand acceleration
void ParticleManager::UpdateAllParticles(FP_LONG dt)
{
	auto& m_scene = *Scene::Get();
	auto& velocities = m_scene.componentRegistry->GetComponentsByType<Particle_Velocity>();
	auto& accelerations = m_scene.componentRegistry->GetComponentsByType<Particle_Acceleration>();
	auto& positions = m_scene.componentRegistry->GetComponentsByType<Particle_Position>();

	if (velocities.size() != accelerations.size() || positions.size() != velocities.size())
	{
		throw(std::runtime_error("ParticleManager:: particle vectors must be the same size"));
	}

	auto number = velocities.size();

	for (int i = 0; i < number; i++)
	{
		IntegrateAcceleration(dt, velocities[i], accelerations[i]);
		IntegrateVelocity(dt, positions[i], velocities[i]);
	}
}
