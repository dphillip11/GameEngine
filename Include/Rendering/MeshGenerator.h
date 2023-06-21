#pragma once
#include <cmath>

class MeshGenerator
{
public:
	static void GenerateBallVertices(int* indices, float* vertices, int NUM_SEGMENTS)
	{
		const float PI = static_cast<float>(3.14159265);

		for (int i = 0; i < NUM_SEGMENTS; i++) {
			float angle1 = static_cast<float>(i) / NUM_SEGMENTS * 2 * PI;
			float y = std::sin(angle1);
			float r = std::cos(angle1);

			for (int j = 0; j < NUM_SEGMENTS; j++) {
				float angle2 = static_cast<float>(j) / NUM_SEGMENTS * 2.0f * PI;
				float x = r * std::cos(angle2);
				float z = r * std::sin(angle2);

				int vertexIndex = (i * NUM_SEGMENTS + j) * 3;
				vertices[vertexIndex + 0] = x;
				vertices[vertexIndex + 1] = y;
				vertices[vertexIndex + 2] = z;
			}
		}

		int index = 0;
		for (int i = 0; i < NUM_SEGMENTS - 1; i++) {
			for (int j = 0; j < NUM_SEGMENTS; j++) {
				indices[index++] = i * NUM_SEGMENTS + j;
				indices[index++] = (i + 1) * NUM_SEGMENTS + j;
				indices[index++] = (i + 1) * NUM_SEGMENTS + (j + 1) % NUM_SEGMENTS;

				indices[index++] = i * NUM_SEGMENTS + j;
				indices[index++] = (i + 1) * NUM_SEGMENTS + (j + 1) % NUM_SEGMENTS;
				indices[index++] = i * NUM_SEGMENTS + (j + 1) % NUM_SEGMENTS;
			}
		}
	}
};
