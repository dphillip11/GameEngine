#include "PCH/pch.h"
#include "Tests/Tests.h"
#include "Rendering/Window.h"
#include "Scene/Scene.h"
#include "Tests/Test_Hashed_Vector.h"
#include "Tests/Testregistry.h"

int main() {

	Window window(1920, 1080, "window");

	Scene scene;

	for (int i = 0; i < 10; i++)
	{
		EntityRef particle = scene.particleManager->NewParticle();
		particle.getComponent<Particle_Position>().value = Vector3(10 * i - 25, 0, 0);

	};
	scene.componentRegistry->GetComponentByComponentID<Particle_Velocity>(3).value = Vector3(-1, 0, 0);
	BuoyantForce buoyant(0, 10);
	scene.entityRegistry->GetRef(3);
	scene.forceRegistry->AddForceGenerator(&buoyant, scene.entityRegistry->GetRef(3));
	GravityForce gravity(Vector3(0, -10, 0));
	scene.forceRegistry->AddForceGenerator(&gravity, scene.entityRegistry->GetRef(3));
	scene.forceRegistry->AddForceGenerator(&gravity, scene.entityRegistry->GetRef(4));
	SpringForce spring(scene.entityRegistry->GetRef(3), 0.4, 4);
	scene.forceRegistry->AddForceGenerator(&spring, scene.entityRegistry->GetRef(4));
	scene.lineRenderer->DrawLine({ -25, 0, 0 }, { 75, 0, 0 });
	scene.lineRenderer->SetLineThickness(2);
	while (!window.closed())
	{
		static double previousTime;
		double currentTime = glfwGetTime();
		double dt = currentTime - previousTime;
		previousTime = glfwGetTime();
		window.update();
		scene.Update(dt);
		scene.Render();
	}
	TestSuite::RunTests();
	//testHashedVector();
	//testHashedVector2();
	//test_registry();

}