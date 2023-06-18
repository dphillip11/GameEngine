#include "PCH/pch.h"
#include "Rendering/ParticleRenderer.h"
#include "Managers/BufferManager.h"
#include "Rendering/MeshGenerator.h"

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

ParticleRenderer::ParticleRenderer(Scene& scene)
	:particle_mesh(MeshRegistry::GetInstance().GetMesh("Particle")), camera(Camera(glm::vec3(0, 0, -50), glm::vec3(0, 0, 0))), m_scene(scene)
{
	particleShader = std::make_unique<Shader>("Source/Shaders/batchBall.hlsl", "Source/Shaders/ball.hlsl");

	//set up mesh
	std::vector<float> vertices;
	std::vector<int> indices;
	MeshGenerator::GenerateBallVertices(indices, vertices, NUM_SEGMENTS);
	std::vector<glm::vec3> vec3_vertices = convertFloatVecToVec3(vertices);
	glGenVertexArrays(1, &VAO_particles);
	glGenBuffers(1, &particle_mesh.VBO);
	glGenBuffers(1, &particle_mesh.EBO);
	BufferManager::setVertices(&vertices[0], vertices.size(), VAO_particles, particle_mesh.VBO);
	BufferManager::setIndices(&indices[0], indices.size(), particle_mesh.EBO);
	particle_mesh.setEBO = true;
	BufferManager::setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	//set up position and size buffers
	auto& particle_positions = m_scene.componentRegistry->GetComponentsByType<Particle_position>();
	glGenBuffers(1, &VBO_particle_position);
	glGenBuffers(1, &VBO_particle_size);
	BufferManager::setVertices(&particle_positions[0], particle_positions.size(), VAO_particles, VBO_particle_position);
	BufferManager::setAttributes(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	glVertexAttribDivisor(1, 1);
	auto& particle_sizes = m_scene.componentRegistry->GetComponentsByType<Particle_size>();
	glGenBuffers(1, &VBO_particle_size);
	BufferManager::setVertices(&particle_sizes[0], particle_sizes.size(), VAO_particles, VBO_particle_size);
	BufferManager::setAttributes(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)(0));
	glVertexAttribDivisor(2, 1);
}

void ParticleRenderer::DrawParticles()
{
	auto& particle_positions = m_scene.componentRegistry->GetComponentsByType<Particle_position>();
	auto& particle_sizes = m_scene.componentRegistry->GetComponentsByType<Particle_size>();
	if (particle_positions.size() == 0)
		return;
	particleShader->Use();

	glm::mat4 VP = camera.projection * camera.lookAt();
	particleShader->setMat4("VP", VP);
	particleShader->setVec3("viewPos", camera._position);

	// Bind the particle mesh and set up its attributes
	BufferManager::Bind(VAO_particles, particle_mesh.VBO, particle_mesh.EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_particle_position);
	glBufferData(GL_ARRAY_BUFFER, particle_positions.size() * sizeof(Vector3), &particle_positions[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_particle_size);
	glBufferData(GL_ARRAY_BUFFER, particle_sizes.size() * sizeof(float), &particle_sizes[0], GL_STATIC_DRAW);
	// Draw the particles using instanced rendering
	glDrawElementsInstanced(GL_TRIANGLES, particle_mesh.indexCount, GL_UNSIGNED_INT, 0, static_cast<GLsizei>(particle_positions.size()));

	// Unbind the particle mesh
	BufferManager::Unbind();

	// Stop using the particle shader
	particleShader->Unuse();
}
