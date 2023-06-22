#include "PCH/pch.h"
#include "Macros/macros.h"
#include "Physics/ForceGenerator.h"

#if (DRAW_SPRINGS)
#include "Scene/scene.h"
#endif


void GravityForce::ApplyForce(EntityRef entity, FP_LONG dt) {
	// Check object doesn't have infinite mass.
	if (entity.getComponent<Particle_InverseMass>().value == 0) return;
	entity.getComponent<Particle_Acceleration>().value += m_gravity;
}

void ConstantForce::ApplyForce(EntityRef entity, FP_LONG dt) {
	// Check object doesn't have infinite mass.
	if (entity.getComponent<Particle_InverseMass>().value == 0) return;
	entity.getComponent<Particle_Acceleration>().value += m_force * entity.getComponent<Particle_InverseMass>().value;
}


void DragForce::ApplyForce(EntityRef entity, FP_LONG dt)
{
	if (entity.getComponent<Particle_InverseMass>().value == 0) return;
	auto speed = entity.getComponent<Particle_Velocity>().value.Length();
	FP drag = m_k1 * speed + m_k2 * speed * speed;
	// Calculate the final force and apply it.
	Vector3 force = entity.getComponent<Particle_Velocity>().value.Normalise() * -drag;
	entity.getComponent<Particle_Acceleration>().value += force * entity.getComponent<Particle_InverseMass>().value;
};

void SpringForce::ApplyForce(EntityRef entity, FP_LONG dt) {
	//missing other end of spring
	if (m_other.m_entityID == -1)
		return;
	//both particles have infinite mass
	if (m_other.getComponent<Particle_InverseMass>().value == 0 && entity.getComponent<Particle_InverseMass>().value == 0)
		return;
	//force oriented towards particle
	Vector3 force = entity.getComponent<Particle_Position>().value - m_other.getComponent<Particle_Position>().value;
	FP extension = force.Length() - m_restLength;
	force = force.Normalise() * extension * m_springConstant;
	if (entity.getComponent<Particle_InverseMass>().value != 0)
		entity.getComponent<Particle_Acceleration>().value += (force * -entity.getComponent<Particle_InverseMass>().value);
	if (m_other.getComponent<Particle_InverseMass>().value != 0)
		m_other.getComponent<Particle_Acceleration>().value += (force * m_other.getComponent<Particle_InverseMass>().value);
#if DRAW_SPRINGS
	Scene::Get()->lineRenderer->DrawLine(entity.getComponent<Particle_Position>().value, m_other.getComponent<Particle_Position>().value);
#endif
}


void BuoyantForce::ApplyForce(EntityRef entity, FP_LONG dt)
{
	if (entity.getComponent<Particle_InverseMass>().value == 0)
		return;
	FP depth = m_surfaceLevel - entity.getComponent<Particle_Position>().value.y;
	// if above surface
	float radius = entity.getComponent<Particle_Radius>().value;
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
	entity.getComponent<Particle_Acceleration>().value += (force * entity.getComponent<Particle_InverseMass>().value);
}