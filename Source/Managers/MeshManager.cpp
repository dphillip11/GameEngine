#include "PCH/pch.h"
#include "Managers/MeshManager.h"
#include "Managers/BufferManager.h"


Mesh& MeshManager::GetMesh(std::string name)
{
	MeshRegistry& mesh_registry = MeshRegistry::GetInstance();
	auto& m = mesh_registry.GetMesh(name);
	glGenVertexArrays(1, &m.VAO);
	glGenBuffers(1, &m.VBO);
	glGenBuffers(1, &m.VBO_normal);
	glGenBuffers(1, &m.VBO_texture);
	glGenBuffers(1, &m.EBO);
	return m;
}

void MeshManager::setVertices(Mesh& mesh, const std::vector<glm::vec3>& vertices)
{
	BufferManager::setVertices(vertices, mesh.VAO, mesh.VBO);
	mesh.vertexCount = vertices.size();
}

void MeshManager::setIndices(Mesh& mesh, const std::vector<int>& indices)
{
	BufferManager::setIndices(indices, mesh.EBO);
	mesh.indexCount = indices.size();
	mesh.setEBO = true;
}

void MeshManager::setAttributes(const Mesh&, int vaoPos, int count, GLenum type, bool normalized, int stride, const void* pos)
{
	BufferManager::setAttributes(vaoPos, count, type, normalized, stride, pos);
}
void MeshManager::Draw(const Mesh& mesh, GLenum fillMode, GLenum drawMode)
{
	Bind(mesh);
	BufferManager::Draw(mesh.setEBO, mesh.setEBO ? mesh.indexCount : mesh.vertexCount, fillMode, drawMode);
	Unbind();
}

void MeshManager::Bind(const Mesh& mesh)
{
	BufferManager::Bind(mesh.VAO, mesh.VBO, mesh.EBO);
}

void MeshManager::Unbind()
{
	BufferManager::Unbind();
}