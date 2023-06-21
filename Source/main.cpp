#include "PCH/pch.h"
#include "Tests/Tests.h"
#include "Rendering/Window.h"
#include "Scene/Scene.h"
#include "Tests/Test_Hashed_Vector.h"

int main() {

	Window window(1920, 1080, "window");

	Scene scene;

	for (int i = 0; i < 10; i++)
	{
		EntityRef particle = scene.particleManager->NewParticle();
		particle.getComponent<Particle_Position>().value = Vector3(10 * i - 25, 0, 0);

	};


	while (!window.closed())
	{
		static double previousTime;
		double currentTime = glfwGetTime();
		double dt = currentTime - previousTime;
		previousTime = glfwGetTime();

		scene.particleRenderer->DrawParticles();
		window.update();
		scene.Update(dt);
	}
	//TestSuite::RunTests();
	//testHashedVector();
	//testHashedVector2();

}