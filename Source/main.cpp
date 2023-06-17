#include "PCH/pch.h"
#include "Tests/Tests.h"
#include "Rendering/Window.h"
#include "Scene/Scene.h"
#include "Tests/Test_Hashed_Vector.h"

int main() {

	Window window(1920, 1080, "window");

	Scene scene;
	Entity scene_entity;
	auto g = GravityForce(Vector3(0, -10, 0));
	auto buoyancy = BuoyantForce(0, 5);
	for (int i = 0; i < 10; i++)
	{
		Particle* p = scene.componentRegistry->RegisterComponent<Particle>(scene_entity);
		if (i == 4)
		{
			auto drag = DragForce(1, 0.2);
			scene.forceRegistry->AddForceGenerator(&drag, p);
		}
		p->position = Vector3(5 * i - 25, 0, 0);
		p->radius = 1 + (i * 0.1f);
		scene.forceRegistry->AddForceGenerator(&g, p);
		scene.forceRegistry->AddForceGenerator(&buoyancy, p);
	};
	Particle* p1 = scene.componentRegistry->RegisterComponent<Particle>(scene_entity);
	Particle* p2 = scene.componentRegistry->RegisterComponent<Particle>(scene_entity);
	auto spring = SpringForce(p2, 9, 6);
	p1->velocity = (0, 0, 1);
	p1->position = { 10,0,0 };
	p2->position = { -10,5,0 };
	p2->radius = 5;
	p2->inverse_mass = 0.5;
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