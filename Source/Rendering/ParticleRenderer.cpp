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

ParticleRenderer::ParticleRenderer(std::vector<Particle>& _particles)
	:particle_mesh(MeshManager::GetMesh("Particle")), camera(Camera(glm::vec3(0, 0, -50), glm::vec3(0, 0, 0))), particles(_particles)
{
	particleShader = std::make_unique<Shader>("Source/Shaders/batchBall.hlsl", "Source/Shaders/ball.hlsl");

	std::vector<float> vertices;
	std::vector<int> indices;
	MeshGenerator::GenerateBallVertices(indices, vertices, NUM_SEGMENTS);
	std::vector<glm::vec3> vec3_vertices = convertFloatVecToVec3(vertices);
	MeshManager::setVertices(particle_mesh, vec3_vertices);
	MeshManager::setIndices(particle_mesh, indices);
	MeshManager::setAttributes(particle_mesh, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glGenBuffers(1, &VBO_particles);
	glBindVertexArray(particle_mesh.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_particles);
	glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), nullptr, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(offsetof(Particle, position)));
	glVertexAttribDivisor(1, 1);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(offsetof(Particle, radius)));
	glVertexAttribDivisor(2, 1);
}

void ParticleRenderer::DrawParticles()
{
	if (particles.size() == 0)
		return;
	particleShader->Use();

	glm::mat4 VP = camera.projection * camera.lookAt();
	particleShader->setMat4("VP", VP);
	particleShader->setVec3("viewPos", camera._position);

	// Bind the particle mesh and set up its attributes
	MeshManager::Bind(particle_mesh);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_particles);
	glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), &particles[0], GL_STATIC_DRAW);
	// Draw the particles using instanced rendering
	glDrawElementsInstanced(GL_TRIANGLES, particle_mesh.indexCount, GL_UNSIGNED_INT, 0, static_cast<GLsizei>(particles.size()));

	// Unbind the particle mesh
	MeshManager::Unbind();

	// Stop using the particle shader
	particleShader->Unuse();
}
