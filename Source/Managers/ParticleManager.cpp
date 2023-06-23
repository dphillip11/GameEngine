#include "PCH/pch.h"
#include "Managers/ParticleManager.h"
#include "Registries/ComponentRegistry.h"
#include "Entity/entity.h"
#include "Scene/scene.h"

Entity ParticleManager::NewParticle()
{
	auto& m_scene = *Scene::Get();
	Entity entity = m_scene.entityRegistry->CreateEntity();
	entity.NewComponent<Particle_Position>();
	entity.NewComponent<Particle_Radius>();
	entity.NewComponent<Particle_InverseMass>();
	entity.NewComponent<Particle_Velocity>();
	entity.NewComponent<Particle_Acceleration>();
	entity.NewComponent<Particle_Restitution>();
	entity.NewComponent<Particle_Friction>();
	entity.NewComponent<Particle_ID>(entity.m_id);
	return entity;
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
	auto& velocities = m_scene.componentRegistry->GetContainer<Particle_Velocity>().getVector();
	auto& accelerations = m_scene.componentRegistry->GetContainer<Particle_Acceleration>().getVector();
	auto& positions = m_scene.componentRegistry->GetContainer<Particle_Position>().getVector();

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
