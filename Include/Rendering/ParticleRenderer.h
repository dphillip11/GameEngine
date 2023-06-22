#pragma once
#include "Components/components.h"
#include <vector>
#include "Registries/MeshRegistry.h"
#include "Rendering/Shader.h"

class ParticleRenderer
{
private:
	Mesh& particle_mesh;
	unsigned int VBO_particle_size;
	unsigned int VBO_particle_position;
	unsigned int VAO_particles;
	std::unique_ptr<Shader> particleShader;

public:
	ParticleRenderer();
	void DrawParticles();
};

