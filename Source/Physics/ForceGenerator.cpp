#include "PCH/pch.h"
#include "Physics/ForceGenerator.h"

void GravityForce::ApplyForce(Particle* particle, FP_LONG dt) {
	// Check object doesn't have infinite mass.
	if (particle->inverse_mass == 0 || !particle->Active) return;
	particle->acceleration += m_gravity;
}

void ConstantForce::ApplyForce(Particle* particle, FP_LONG dt) {
	// Check object doesn't have infinite mass.
	if (particle->inverse_mass == 0 || !particle->Active) return;
	particle->acceleration += m_force * particle->inverse_mass;
}


void DragForce::ApplyForce(Particle* particle, FP_LONG dt)
{
	if (particle->inverse_mass == 0 || !particle->Active) return;
	auto speed = particle->velocity.Length();
	FP drag = m_k1 * speed + m_k2 * speed * speed;
	// Calculate the final force and apply it.
	Vector3 force = particle->velocity.Normalise() * -drag;
	particle->acceleration += force * particle->inverse_mass;
};

void SpringForce::ApplyForce(Particle* particle, FP_LONG dt) {
	//missing other end of spring
	if (m_other == nullptr)
		return;
	//either particle is inactive
	if (!m_other->Active || !particle->Active)
		return;
	//both particles have infinite mass
	if (!m_other->inverse_mass == 0 && particle->inverse_mass == 0)
		return;
	//force oriented towards particle
	Vector3 force = particle->position - m_other->position;
	FP extension = force.Length() - m_restLength;
	force = force.Normalise() * extension * m_springConstant;
	if (particle->inverse_mass != 0)
		particle->acceleration += (force * -particle->inverse_mass);
	if (m_other->inverse_mass != 0)
		m_other->acceleration += (force * m_other->inverse_mass);
}


void BuoyantForce::ApplyForce(Particle* particle, FP_LONG dt)
{
	if (particle->inverse_mass == 0)
		return;
	FP depth = m_surfaceLevel - particle->position.y;
	// if above surface
	if (depth < -particle->radius)
		return;
	// forced is constant once fully submerged
	depth = fmin(depth, particle->radius);
	static FP third = (FP(1) / 3);
	//integral of sphere from -radius to depth, h
	//[xr2 - x3/3] expanded and factorised
	FP submergedVolume = (depth - 2 * particle->radius) * (depth + particle->radius) * (depth + particle->radius) * -third * M_PI;
	Vector3 force;
	force.y = submergedVolume * m_liquidDensity;
	particle->acceleration += (force * particle->inverse_mass);
}