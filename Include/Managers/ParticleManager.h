#pragma once
#include "Geometry/Precision.h"
#include "Components/Components.h"

class ParticleManager
{
private:
	Scene& m_scene;
public:
	ParticleManager(Scene& scene) :m_scene(scene) {}
	// updates velocity based on acceleration and time
	void IntegrateAcceleration(FP_LONG dt, Particle& particle);
	// update position based on velocity and time
	void IntegrateVelocity(FP_LONG dt, Particle& particle);
	// updates particle positions based on position, velocity and acceleration
	void UpdateAllParticles(FP_LONG dt);
};

