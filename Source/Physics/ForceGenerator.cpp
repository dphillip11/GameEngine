#include "PCH/pch.h"
#include "Macros/macros.h"
#include "Physics/ForceGenerator.h"
#include "Scene/scene.h"

#if (DRAW_SPRINGS)
#include "Scene/scene.h"
#endif

namespace Forces {

	void ApplyForces() {
		ComponentRegistry& registry = *Scene::Get()->componentRegistry;
		auto& g_force_components = registry.GetComponentsByType<GravityForce>();
		for (auto& component : g_force_components)
		{
			ApplyGravityForce(component.entity, component.m_gravity);
		}

		// Apply constant forces
		auto& c_force_components = registry.GetComponentsByType<ConstantForce>();
		for (auto& component : c_force_components) {
			ApplyConstantForce(component.entity, component.m_force);
		}

		// Apply drag forces
		auto& d_force_components = registry.GetComponentsByType<DragForce>();
		for (auto& component : d_force_components) {
			ApplyDragForce(component.entity, component.m_k1, component.m_k2);
		}

		// Apply spring forces
		auto& s_force_components = registry.GetComponentsByType<SpringForce>();
		for (auto& component : s_force_components) {
			ApplySpringForce(component.entity, component.m_other, component.m_springConstant, component.m_restLength);
		}

		// Apply buoyant forces
		auto& b_force_components = registry.GetComponentsByType<BuoyantForce>();
		for (auto& component : b_force_components) {
			ApplyBuoyantForce(component.entity, component.m_surfaceLevel, component.m_liquidDensity);
		}
	}


	void ApplyGravityForce(EntityRef entity, const Vector3& gravity) {
		// Check object doesn't have infinite mass.
		if (entity.getComponent<Particle_InverseMass>().value == 0) return;
		entity.getComponent<Particle_Acceleration>().value += gravity;
	}

	void ApplyConstantForce(EntityRef entity, const Vector3& force) {
		// Check object doesn't have infinite mass.
		if (entity.getComponent<Particle_InverseMass>().value == 0) return;
		entity.getComponent<Particle_Acceleration>().value += force * entity.getComponent<Particle_InverseMass>().value;
	}


	void ApplyDragForce(EntityRef entity, FP k1, FP k2)
	{
		if (entity.getComponent<Particle_InverseMass>().value == 0) return;
		auto speed = entity.getComponent<Particle_Velocity>().value.Length();
		FP drag = k1 * speed + k2 * speed * speed;
		// Calculate the final force and apply it.
		Vector3 force = entity.getComponent<Particle_Velocity>().value.Normalise() * -drag;
		entity.getComponent<Particle_Acceleration>().value += force * entity.getComponent<Particle_InverseMass>().value;
	};

	void ApplySpringForce(EntityRef entity, EntityRef other, FP springConstant, FP restLength) {
		//missing other end of spring
		if (other.m_entityID == -1)
			return;
		//both particles have infinite mass
		if (other.getComponent<Particle_InverseMass>().value == 0 && entity.getComponent<Particle_InverseMass>().value == 0)
			return;
		//force oriented towards particle
		Vector3 force = entity.getComponent<Particle_Position>().value - other.getComponent<Particle_Position>().value;
		FP extension = force.Length() - restLength;
		force = force.Normalise() * extension * springConstant;
		if (entity.getComponent<Particle_InverseMass>().value != 0)
			entity.getComponent<Particle_Acceleration>().value += (force * -entity.getComponent<Particle_InverseMass>().value);
		if (other.getComponent<Particle_InverseMass>().value != 0)
			other.getComponent<Particle_Acceleration>().value += (force * other.getComponent<Particle_InverseMass>().value);
#if DRAW_SPRINGS
		Scene::Get()->lineRenderer->DrawLine(entity.getComponent<Particle_Position>().value, other.getComponent<Particle_Position>().value);
#endif
	}

	void ApplyBuoyantForce(EntityRef entity, FP surfaceLevel, FP liquidDensity)
	{
		if (entity.getComponent<Particle_InverseMass>().value == 0)
			return;
		FP depth = surfaceLevel - entity.getComponent<Particle_Position>().value.y;
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
		force.y = submergedVolume * liquidDensity;
		entity.getComponent<Particle_Acceleration>().value += (force * entity.getComponent<Particle_InverseMass>().value);
	}
}