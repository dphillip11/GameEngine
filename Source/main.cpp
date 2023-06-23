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
	Entity anchor = scene.particleManager->NewParticle();
	anchor.GetComponent<Particle_Position>().value = Vector3(-35, 0, 0);
	anchor.GetComponent<Particle_InverseMass>().value = 0;
	anchor.GetComponent<Particle_Radius>().value = 5;
	Entity previous = anchor;
	GravityForce g;
	g.m_gravity = { 0, -10, 0 };
	for (int i = 0; i < 10; i++)
	{
		Entity particle = scene.particleManager->NewParticle();
		particle.GetComponent<Particle_Position>().value = Vector3(10 * i - 25, 0, 0);
		g.entity = particle;
		particle.AddComponent(g);
		SpringForce spring;
		spring.entity = particle;
		spring.m_other = previous;
		spring.m_restLength = 2;
		spring.m_springConstant = 5;
		particle.AddComponent(spring);
		previous = particle;
		if (i == 9)
		{
			particle.GetComponent<Particle_InverseMass>().value = 0;
			particle.GetComponent<Particle_Radius>().value = 5;
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
	test_registry();

}