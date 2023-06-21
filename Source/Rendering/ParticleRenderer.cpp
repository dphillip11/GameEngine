#include "PCH/pch.h"
#include "Rendering/ParticleRenderer.h"
#include "Managers/BufferManager.h"
#include "Rendering/MeshGenerator.h"
#include "Scene/scene.h"

#define NUM_SEGMENTS  40

std::vector<glm::vec3> convertFloatVecToVec3(std::vector<float>& input)
{
	std::vector<glm::vec3> output;
	for (int i = 0; i < input.size(); i++)
	{
		switch (i % 3)
		{
		case 0:
			output.push_back(glm::vec3(0));
			output.back().x = input[i];
			break;
		case 1:
			output.back().y = input[i];
			break;
		case 2:
			output.back().z = input[i];
			break;
		}
	}
	return output;
}

ParticleRenderer::ParticleRenderer()
	:particle_mesh(MeshRegistry::GetInstance().GetMesh("Particle")), camera(Camera(glm::vec3(0, 0, -50), glm::vec3(0, 0, 0)))
{
	particleShader = std::make_unique<Shader>("Source/Shaders/batchBall.hlsl", "Source/Shaders/ball.hlsl");

	//set up mesh
	std::vector<float> vertices;
	std::vector<int> indices;
	MeshGenerator::GenerateBallVertices(indices, vertices, NUM_SEGMENTS);
	std::vector<glm::vec3> vec3_vertices = convertFloatVecToVec3(vertices);
	particle_mesh.indexCount = indices.size();
	particle_mesh.vertexCount = vertices.size() / 3;

	glGenVertexArrays(1, &VAO_particles);
	glGenBuffers(1, &particle_mesh.VBO);
	glGenBuffers(1, &particle_mesh.EBO);
	glGenBuffers(1, &VBO_particle_position);
	glGenBuffers(1, &VBO_particle_size);

	BufferManager::setVertices(&vertices[0], vertices.size(), VAO_particles, particle_mesh.VBO);
	BufferManager::setIndices(&indices[0], indices.size(), particle_mesh.EBO);
	BufferManager::setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	particle_mesh.setEBO = true;

	//set up position and size buffers
	auto& m_scene = *Scene::Get();
	auto& particle_positions = m_scene.componentRegistry->GetComponentsByType<Particle_Position>();
	auto& particle_sizes = m_scene.componentRegistry->GetComponentsByType<Particle_Radius>();

	BufferManager::setVertices(particle_positions.data(), particle_positions.size(), VAO_particles, VBO_particle_position);
	BufferManager::setAttributes(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	glVertexAttribDivisor(1, 1);

	BufferManager::setVertices(particle_sizes.data(), particle_sizes.size(), VAO_particles, VBO_particle_size);
	BufferManager::setAttributes(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)(0));
	glVertexAttribDivisor(2, 1);
}

void ParticleRenderer::DrawParticles()
{
	auto& m_scene = *Scene::Get();
	auto& particle_positions = m_scene.componentRegistry->GetComponentsByType<Particle_Position>();
	auto& particle_sizes = m_scene.componentRegistry->GetComponentsByType<Particle_Radius>();
	if (particle_positions.size() == 0)
		return;
	particleShader->Use();

	glm::mat4 VP = camera.projection * camera.lookAt();
	particleShader->setMat4("VP", VP);
	particleShader->setVec3("viewPos", camera._position);

	// Bind the particle mesh and set up its attributes
	BufferManager::Bind(VAO_particles, particle_mesh.VBO, particle_mesh.EBO);
	BufferManager::setVertices(particle_positions.data(), particle_positions.size(), VAO_particles, VBO_particle_position);
	BufferManager::setVertices(particle_sizes.data(), particle_sizes.size(), VAO_particles, VBO_particle_size);
	// Draw the particles using instanced rendering
	glDrawElementsInstanced(GL_TRIANGLES, particle_mesh.indexCount, GL_UNSIGNED_INT, 0, static_cast<GLsizei>(particle_positions.size()));

	// Unbind the particle mesh
	BufferManager::Unbind();

	// Stop using the particle shader
	particleShader->Unuse();
}
