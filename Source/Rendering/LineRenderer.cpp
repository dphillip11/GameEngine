#include "PCH/pch.h"
#include "Rendering/LineRenderer.h"
#include "Scene/scene.h"
#include "Managers/BufferManager.h"


LineRenderer::LineRenderer() {
	lineShader = std::make_unique<Shader>("Source/Shaders/LineVertexShader.hlsl", "Source/Shaders/LineFragmentShader.hlsl");
	entity = Scene::Get()->entityRegistry->CreateEntity();
	glGenVertexArrays(1, &VAO_line_renderer);
	glGenBuffers(1, &VBO_line_color);
	glGenBuffers(1, &VBO_line_coordinates);

	glBindVertexArray(VAO_line_renderer);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_line_coordinates);
	BufferManager::setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

	glBindBuffer(GL_ARRAY_BUFFER, VBO_line_color);
	BufferManager::setAttributes(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

	BufferManager::Unbind();
}

void LineRenderer::SetLineThickness(float thickness)
{
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(thickness);
}

void LineRenderer::DrawLines() {

	auto& m_scene = *Scene::Get();
	auto& m_camera = m_scene.camera;
	auto& registry = Scene::Get()->componentRegistry;

	auto& line_coords = registry->GetContainer<Line_Coordinates>().getVector();
	auto& line_colors = registry->GetContainer<Line_Color>().getVector();

	lineShader->Use();
	lineShader->setMat4("uView", m_camera.view());
	lineShader->setMat4("uProjection", m_camera.projection);

	BufferManager::setVertices(line_coords.data(), line_coords.size() * 6, VAO_line_renderer, VBO_line_coordinates);
	BufferManager::setVertices(line_colors.data(), line_colors.size() * 6, VAO_line_renderer, VBO_line_color);

	glDrawArrays(GL_LINES, 0, line_coords.size() * 2);

	lineShader->Unuse();
	BufferManager::Unbind();
}

// adds line components to registry
void LineRenderer::DrawLine(Vector3 A, Vector3 B, Vector3 color)
{
	auto& registry = Scene::Get()->componentRegistry;
	Line_Coordinates l_coords{ A,B };
	Line_Color l_color{ color, color };
	entity.AddComponent(l_coords);
	entity.AddComponent(l_color);
}

void LineRenderer::DeleteLines()
{
	auto& registry = Scene::Get()->componentRegistry;
	registry->GetContainer<Line_Coordinates>().clear();
	registry->GetContainer<Line_Color>().clear();
	entity.ClearComponents();
}


