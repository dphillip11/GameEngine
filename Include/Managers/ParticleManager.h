#pragma once
#include "Geometry/Precision.h"
#include "Components/Components.h"

class ParticleManager
{
private:
	std::vector<Particle>& m_particle_registry;
public:
	ParticleManager(std::vector<Particle>& particle_registry) :m_particle_registry(particle_registry) {}
	// updates velocity based on acceleration and time
	void IntegrateAcceleration(FP_LONG dt, Particle& particle);
	// update position based on velocity and time
	void IntegrateVelocity(FP_LONG dt, Particle& particle);
	// updates particle positions based on position, velocity and acceleration
	void UpdateAllParticles(FP_LONG dt);
};

