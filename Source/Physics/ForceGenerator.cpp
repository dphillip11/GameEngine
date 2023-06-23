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
		auto& g_force_components = registry.GetContainer<GravityForce>().getVector();
		for (auto& component : g_force_components)
		{
			ApplyGravityForce(component.entity, component.m_gravity);
		}

		// Apply constant forces
		auto& c_force_components = registry.GetContainer<ConstantForce>().getVector();;
		for (auto& component : c_force_components) {
			ApplyConstantForce(component.entity, component.m_force);
		}

		// Apply drag forces
		auto& d_force_components = registry.GetContainer<DragForce>().getVector();
		for (auto& component : d_force_components) {
			ApplyDragForce(component.entity, component.m_k1, component.m_k2);
		}

		// Apply spring forces
		auto& s_force_components = registry.GetContainer<SpringForce>().getVector();
		for (auto& component : s_force_components) {
			ApplySpringForce(component.entity, component.m_other, component.m_springConstant, component.m_restLength);
		}

		// Apply buoyant forces
		auto& b_force_components = registry.GetContainer<BuoyantForce>().getVector();;
		for (auto& component : b_force_components) {
			ApplyBuoyantForce(component.entity, component.m_surfaceLevel, component.m_liquidDensity);
		}
	}


	void ApplyGravityForce(Entity entity, const Vector3& gravity) {
		// Check object doesn't have infinite mass.
		if (entity.GetComponent<Particle_InverseMass>().value == 0) return;
		entity.GetComponent<Particle_Acceleration>(0).value += gravity;
	}

	void ApplyConstantForce(Entity entity, const Vector3& force) {
		// Check object doesn't have infinite mass.
		if (entity.GetComponent<Particle_InverseMass>().value == 0) return;
		entity.GetComponent<Particle_Acceleration>().value += force * entity.GetComponent<Particle_InverseMass>().value;
	}


	void ApplyDragForce(Entity entity, FP k1, FP k2)
	{
		if (entity.GetComponent<Particle_InverseMass>().value == 0) return;
		auto speed = entity.GetComponent<Particle_Velocity>().value.Length();
		FP drag = k1 * speed + k2 * speed * speed;
		// Calculate the final force and apply it.
		Vector3 force = entity.GetComponent<Particle_Velocity>().value.Normalise() * -drag;
		entity.GetComponent<Particle_Acceleration>().value += force * entity.GetComponent<Particle_InverseMass>().value;
	};

	void ApplySpringForce(Entity entity, Entity other, FP springConstant, FP restLength) {
		//missing other end of spring
		if (other.m_id == -1)
			return;
		//both particles have infinite mass
		if (other.GetComponent<Particle_InverseMass>().value == 0 && entity.GetComponent<Particle_InverseMass>().value == 0)
			return;
		//force oriented towards particle
		Vector3 force = entity.GetComponent<Particle_Position>().value - other.GetComponent<Particle_Position>().value;
		FP extension = force.Length() - restLength;
		force = force.Normalise() * extension * springConstant;
		if (entity.GetComponent<Particle_InverseMass>().value != 0)
			entity.GetComponent<Particle_Acceleration>().value += (force * -entity.GetComponent<Particle_InverseMass>().value);
		if (other.GetComponent<Particle_InverseMass>().value != 0)
			other.GetComponent<Particle_Acceleration>().value += (force * other.GetComponent<Particle_InverseMass>().value);
#if DRAW_SPRINGS
		Scene::Get()->lineRenderer->DrawLine(entity.GetComponent<Particle_Position>().value, other.GetComponent<Particle_Position>().value);
#endif
	}

	void ApplyBuoyantForce(Entity entity, FP surfaceLevel, FP liquidDensity)
	{
		if (entity.GetComponent<Particle_InverseMass>().value == 0)
			return;
		FP depth = surfaceLevel - entity.GetComponent<Particle_Position>().value.y;
		// if above surface
		float radius = entity.GetComponent<Particle_Radius>().value;
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
		entity.GetComponent<Particle_Acceleration>().value += (force * entity.GetComponent<Particle_InverseMass>().value);
	}
}