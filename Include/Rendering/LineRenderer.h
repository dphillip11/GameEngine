#pragma once
#include <memory>
#include "Rendering/Shader.h"
#include "Entity/entity.h"

class LineRenderer
{
private:
	unsigned int VBO_line_coordinates = 0;
	unsigned int VBO_line_color;
	unsigned int VAO_line_renderer = 0;
	std::unique_ptr<Shader> lineShader = nullptr;
	Entity entity;

public:
	LineRenderer();
	void DrawLines();
	void SetLineThickness(float thickness);
	void DrawLine(Vector3 A, Vector3 B, Vector3 colorA = { 1, 0, 0 });
	void DeleteLines();
};
