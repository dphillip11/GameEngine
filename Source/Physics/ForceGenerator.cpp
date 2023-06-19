#include "PCH/pch.h"
#include "Physics/ForceGenerator.h"

void GravityForce::ApplyForce(EntityRef entity, FP_LONG dt) {
	// Check object doesn't have infinite mass.
	if (entity.get<Particle_InverseMass>().value == 0) return;
	entity.get<Particle_Acceleration>().value += m_gravity;
}

void ConstantForce::ApplyForce(EntityRef entity, FP_LONG dt) {
	// Check object doesn't have infinite mass.
	if (entity.get<Particle_InverseMass>().value == 0) return;
	entity.get<Particle_Acceleration>().value += m_force * entity.get<Particle_InverseMass>().value;
}


void DragForce::ApplyForce(EntityRef entity, FP_LONG dt)
{
	if (entity.get<Particle_InverseMass>().value == 0) return;
	auto speed = entity.get<Particle_Velocity>().value.Length();
	FP drag = m_k1 * speed + m_k2 * speed * speed;
	// Calculate the final force and apply it.
	Vector3 force = entity.get<Particle_Velocity>().value.Normalise() * -drag;
	entity.get<Particle_Acceleration>().value += force * entity.get<Particle_InverseMass>().value;
};

void SpringForce::ApplyForce(EntityRef entity, FP_LONG dt) {
	//missing other end of spring
	if (m_other.m_entityID == -1)
		return;
	//both particles have infinite mass
	if (m_other.get<Particle_InverseMass>().value == 0 && entity.get<Particle_InverseMass>().value == 0)
		return;
	//force oriented towards particle
	Vector3 force = entity.get<Particle_Position>().value - m_other.get<Particle_Position>().value;
	FP extension = force.Length() - m_restLength;
	force = force.Normalise() * extension * m_springConstant;
	if (entity.get<Particle_InverseMass>().value != 0)
		entity.get<Particle_Acceleration>().value += (force * -entity.get<Particle_InverseMass>().value);
	if (m_other.get<Particle_InverseMass>().value != 0)
		m_other.get<Particle_Acceleration>().value += (force * entity.get<Particle_InverseMass>().value);
}


void BuoyantForce::ApplyForce(EntityRef entity, FP_LONG dt)
{
	if (entity.get<Particle_InverseMass>().value == 0)
		return;
	FP depth = m_surfaceLevel - entity.get<Particle_Position>().value.y;
	// if above surface
	float radius = entity.get<Particle_Radius>().value;
	if (depth < -radius)
		return;
	// forced is constant once fully submerged
	depth = fmin(depth, radius);
	static FP third = (FP(1) / 3);
	//integral of sphere from -radius to depth, h
	//[xr2 - x3/3] expanded and factorised
	FP submergedVolume = (depth - 2 * radius) * (depth + radius) * (depth + radius) * -third * M_PI;
	Vector3 force;
	force.y = submergedVolume * m_liquidDensity;
	entity.get<Particle_Acceleration>().value += (force * entity.get<Particle_InverseMass>().value);
}