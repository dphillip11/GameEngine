#pragma once
#include "Components/components.h"
#include <vector>
#include "Managers/MeshManager.h"
#include "Rendering/Shader.h"
#include "Camera.h"

class ParticleRenderer
{
private:
	Camera camera;
	Mesh& particle_mesh;
	unsigned int VBO_particles;
	unsigned int VAO_particles;
	std::vector<Particle>& particles;
	std::unique_ptr<Shader> particleShader;

public:
	ParticleRenderer(std::vector<Particle>& _particles);
	void DrawParticles();
};

