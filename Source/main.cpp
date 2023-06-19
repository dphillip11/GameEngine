#include "PCH/pch.h"
#include "Tests/Tests.h"
#include "Rendering/Window.h"
#include "Scene/Scene.h"
#include "Tests/Test_Hashed_Vector.h"

int main() {

	Window window(1920, 1080, "window");

	Scene scene;
	auto g = GravityForce(Vector3(0, -10, 0));
	auto buoyancy = BuoyantForce(0, 5);
	for (int i = 0; i < 10; i++)
	{
		EntityRef particle = scene.particleManager->NewParticle();
		if (i == 4)
		{
			auto drag = DragForce(1, 0.2);
			scene.forceRegistry->AddForceGenerator(&drag, particle);
		}
		particle.get<Particle_Position>().value = Vector3(5 * i - 25, 0, 0);
		particle.get<Particle_Position>().value = 1 + (i * 0.1f);
		scene.forceRegistry->AddForceGenerator(&g, particle);
		scene.forceRegistry->AddForceGenerator(&buoyancy, particle);
	};
	EntityRef p1 = scene.particleManager->NewParticle();
	EntityRef p2 = scene.particleManager->NewParticle();
	auto spring = SpringForce(p2, 9, 6);
	p1.get<Particle_Velocity>().value = (0, 0, 1);
	p1.get<Particle_Position>().value = { 10,0,0 };
	p2.get<Particle_Velocity>().value = { -10,5,0 };
	p2.get<Particle_Position>().value = 5;
	p2.get<Particle_InverseMass>().value = 0.5;
	scene.forceRegistry->AddForceGenerator(&spring, p1);
	scene.forceRegistry->AddForceGenerator(&buoyancy, p2);
	scene.forceRegistry->AddForceGenerator(&g, p2);
	scene.forceRegistry->AddForceGenerator(&g, p1);

	while (!window.closed())
	{
		scene.particleRenderer->DrawParticles();
		window.update();
		scene.Update(0.001);
	}
	TestSuite::RunTests();
	testHashedVector();
	testHashedVector2();

}