#include "PCH/pch.h"
#include "Managers/ParticleManager.h"
#include "Registries/ComponentRegistry.h"



// updates velocity based on acceleration and time
void ParticleManager::IntegrateAcceleration(FP_LONG dt, Particle& particle)
{
	particle.velocity += (particle.acceleration * dt);
	particle.acceleration = Vector3(0);
}
// update position based on velocity and time
void ParticleManager::IntegrateVelocity(FP_LONG dt, Particle& particle)
{
	particle.position += (particle.velocity * dt);
}

// updates particle positions based on position, velocityand acceleration
void ParticleManager::UpdateAllParticles(FP_LONG dt)
{
	for (auto& particle : m_particle_registry)
	{
		IntegrateAcceleration(dt, particle);
		IntegrateVelocity(dt, particle);
	}
}
