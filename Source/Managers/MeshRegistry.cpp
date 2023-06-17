#include "PCH/pch.h"
#include "Registries/MeshRegistry.h"
#include "Managers/MeshManager.h"
#include "Tools/Obj.h"

void MeshRegistry::ParseFile(const char* filepath, Mesh& mesh) {
	OBJ mesh_data;
	mesh_data.read(filepath);
	mesh_data.vertices = mesh_data.unravelIndices(mesh_data.vertices, mesh_data.vertexIndices);
	mesh_data.normalMap = mesh_data.unravelIndices(mesh_data.normalMap, mesh_data.normalIndices);
	mesh_data.textureMap = mesh_data.unravelIndices(mesh_data.textureMap, mesh_data.textureIndices);
	mesh.upperBounds = mesh_data.upper_bounds.x, mesh_data.upper_bounds.y, mesh_data.upper_bounds.z;
	mesh.lowerBounds = mesh_data.lower_bounds.x, mesh_data.lower_bounds.y, mesh_data.lower_bounds.z;

	//vertices
	glBindVertexArray(mesh.VAO);
	MeshManager::setVertices(mesh, mesh_data.vertices);
	MeshManager::setAttributes(mesh, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

	//normals
	if (mesh_data.normalMap.size() > 0)
	{
		MeshManager::setVertices(mesh, mesh_data.normalMap);
		MeshManager::setAttributes(mesh, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	}

	//texturemap
	if (mesh_data.textureMap.size() > 0)
	{
		MeshManager::setVertices(mesh, mesh_data.textureMap);
		MeshManager::setAttributes(mesh, 2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	}

}