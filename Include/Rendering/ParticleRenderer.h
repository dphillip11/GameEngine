#pragma once
#include "Components/components.h"
#include <vector>
#include "Registries/MeshRegistry.h"
#include "Scene/Scene.h"
#include "Rendering/Shader.h"
#include "Camera.h"

class ParticleRenderer
{
private:
	Camera camera;
	Mesh& particle_mesh;
	unsigned int VBO_particle_size;
	unsigned int VBO_particle_position;
	unsigned int VAO_particles;
	Scene& m_scene;
	std::unique_ptr<Shader> particleShader;

public:
	ParticleRenderer(Scene& scene);
	void DrawParticles();
};

