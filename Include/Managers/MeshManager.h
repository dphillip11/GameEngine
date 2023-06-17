#pragma once
#include "Registries/MeshRegistry.h"

class MeshManager
{
public:
	static Mesh& GetMesh(std::string name);
	static void setVertices(Mesh& mesh, const std::vector<glm::vec3>& vertices);
	static void setIndices(Mesh& mesh, const std::vector<int>& indices);
	static void setAttributes(const Mesh&, int vaoPos, int count, GLenum type, bool normalized, int stride, const void* pos);
	static void Draw(const Mesh& mesh, GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
	static void Bind(const Mesh& mesh);
	static void Unbind();
};

