#pragma once
#include "Components/Components.h"
#include "Geometry/Precision.h"
#include "Entity/entity.h"

class ForceGenerator {
public:
	virtual void ApplyForce(EntityRef entity, FP_LONG dt) = 0;
};

class GravityForce : public ForceGenerator {
	Vector3 m_gravity;
public:
	GravityForce(const Vector3& gravity) : m_gravity(gravity) {};
	void ApplyForce(EntityRef entity, FP_LONG dt) override;
};

class ConstantForce : public ForceGenerator {
	Vector3 m_force;
public:
	ConstantForce(const Vector3& force) : m_force(force) {};
	void ApplyForce(EntityRef entity, FP_LONG dt) override;
};

class DragForce : public ForceGenerator
{
	FP m_k1, m_k2;
public:
	DragForce(FP k1, FP k2) : m_k1(k1), m_k2(k2) {};
	void ApplyForce(EntityRef entity, FP_LONG dt) override;
};

class SpringForce : public ForceGenerator
{
	EntityRef m_other;
	FP m_springConstant;
	FP m_restLength;
public:
	SpringForce(EntityRef other, FP springConstant, FP restLength) : m_other(other), m_springConstant(springConstant), m_restLength(restLength) {}
	void ApplyForce(EntityRef entity, FP_LONG dt) override;
};

class BuoyantForce : public ForceGenerator
{
	FP m_surfaceLevel;
	FP m_liquidDensity;
public:
	BuoyantForce(FP surfaceLevel, FP liquidDensity = 1000) : m_surfaceLevel(surfaceLevel), m_liquidDensity(liquidDensity) {}
	void ApplyForce(EntityRef entity, FP_LONG dt) override;
};
