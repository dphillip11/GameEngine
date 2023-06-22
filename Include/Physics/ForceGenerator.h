#pragma once
#include "Components/Components.h"
#include "Geometry/Precision.h"
#include "Entity/entity.h"

namespace Forces {
	extern void ApplyForces();
	extern void ApplyGravityForce(EntityRef entity, const Vector3& gravity);
	extern void ApplyConstantForce(EntityRef entity, const Vector3& force);
	extern void ApplyDragForce(EntityRef entity, FP k1, FP k2);
	extern void ApplySpringForce(EntityRef entity, EntityRef other, FP springConstant, FP restLength);
	extern void ApplyBuoyantForce(EntityRef entity, FP surfaceLevel, FP liquidDensity);
}


struct ForceGenerator {
	EntityRef entity;
};

struct GravityForce : ForceGenerator {
	Vector3 m_gravity;
};

struct ConstantForce : ForceGenerator {
	Vector3 m_force;
};

struct DragForce : ForceGenerator {
	FP m_k1, m_k2;
};

struct SpringForce : ForceGenerator {
	EntityRef m_other;
	FP m_springConstant = 1;
	FP m_restLength = 1;
};

struct BuoyantForce : ForceGenerator {
	FP m_surfaceLevel;
	FP m_liquidDensity;
};


