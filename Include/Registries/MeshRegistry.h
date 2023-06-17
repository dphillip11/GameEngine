#pragma once
#include "Components/components.h"
#include "Managers/Singleton.h"
#include <unordered_map>
#include <string>
#include <mutex>

struct Mesh
{
	unsigned int VBO, VAO, EBO, VBO_normal, VBO_texture;
	bool setEBO = false;
	unsigned int vertexCount;
	unsigned int indexCount;
	Vector3 upperBounds;
	Vector3 lowerBounds;
};

class MeshRegistry : public Singleton<MeshRegistry> {
public:

	Mesh& GetMesh(std::string name)
	{
		if (m_Meshes.find(name) != m_Meshes.end()) {
			return m_Meshes[name];
		}
		Mesh mesh;
		m_Meshes[name] = mesh;
		return m_Meshes[name];

	}

	Mesh& LoadMesh(const char* filepath) {
		if (m_Meshes.find(filepath) != m_Meshes.end()) {
			return m_Meshes[filepath];
		}
		std::lock_guard<std::mutex> lock(mesh_load_mutex); // Lock the mutex
		Mesh mesh;
		ParseFile(filepath, mesh);
		m_Meshes[filepath] = mesh;
		return m_Meshes[filepath];
	}


private:
	std::mutex mesh_load_mutex;
	void ParseFile(const char* filepath, Mesh& mesh);
	std::unordered_map<std::string, Mesh> m_Meshes;
};