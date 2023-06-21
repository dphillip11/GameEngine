#pragma once
#include "Geometry/Precision.h"
#include "Components/Components.h"

class EntityRef;

class ParticleManager
{
public:
	EntityRef NewParticle();
	// updates velocity based on acceleration and time
	void IntegrateAcceleration(FP_LONG dt, Particle_Velocity& velocity, Particle_Acceleration& acceleration);
	// update position based on velocity and time
	void IntegrateVelocity(FP_LONG dt, Particle_Position& position, Particle_Velocity& velocity);
	// updates particle positions based on position, velocity and acceleration
	void UpdateAllParticles(FP_LONG dt);
};

