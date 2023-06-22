#include "PCH/pch.h"
#include "Macros/macros.h"
#include "Tests/Tests.h"
#include "Rendering/Window.h"
#include "Scene/Scene.h"
#include "Tests/Test_Hashed_Vector.h"
#include "Tests/Testregistry.h"
#include "GUI/GUI.h"

int main() {

	Window window(1920, 1080, "window");
	GUI gui;
	gui.Init(window.window);
	Scene scene;
	EntityRef anchor = scene.particleManager->NewParticle();
	anchor.getComponent<Particle_Position>().value = Vector3(-35, 0, 0);
	anchor.getComponent<Particle_InverseMass>().value = 0;
	anchor.getComponent<Particle_Radius>().value = 5;
	EntityRef previous = anchor;
	GravityForce gravity(Vector3(0, -10, 0));
	for (int i = 0; i < 10; i++)
	{
		EntityRef particle = scene.particleManager->NewParticle();
		particle.getComponent<Particle_Position>().value = Vector3(10 * i - 25, 0, 0);
		auto spring = SpringForce(previous, 10, 1);
		scene.forceRegistry->AddForceGenerator(spring, particle);
		previous.m_entityID = particle.m_entityID;
		scene.forceRegistry->AddForceGenerator(gravity, particle);
		if (i == 9)
		{
			particle.getComponent<Particle_InverseMass>().value = 0;
			particle.getComponent<Particle_Radius>().value = 5;
		}
	};
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
		gui.Render();
	}
	//TestSuite::RunTests();
	//testHashedVector();
	//testHashedVector2();
	//test_registry();

}