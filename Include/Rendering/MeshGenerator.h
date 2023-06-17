#pragma once
#include <vector>

class MeshGenerator
{
public:
	static void GenerateBallVertices(std::vector<int>& indices, std::vector<float>& vertices, int NUM_SEGMENTS)
	{
		const float PI = (float)3.14159265;

		for (int i = 0; i < NUM_SEGMENTS; i++) {
			float angle1 = (float)i / NUM_SEGMENTS * 2 * PI;
			float y = sin(angle1);
			float r = cos(angle1);

			for (int j = 0; j < NUM_SEGMENTS; j++) {
				//this extra float sometimes causes issues with the secondary draw method
				float angle2 = (float)((float)j / NUM_SEGMENTS * 2.0 * PI);
				float x = r * cos(angle2);
				float z = r * sin(angle2);

				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}
		}

		int index = 0;
		for (int i = 0; i < NUM_SEGMENTS - 1; i++) {
			for (int j = 0; j < NUM_SEGMENTS; j++) {
				indices.push_back(i * NUM_SEGMENTS + j);
				indices.push_back((i + 1) * NUM_SEGMENTS + j);
				indices.push_back((i + 1) * NUM_SEGMENTS + (j + 1) % NUM_SEGMENTS);

				indices.push_back(i * NUM_SEGMENTS + j);
				indices.push_back((i + 1) * NUM_SEGMENTS + (j + 1) % NUM_SEGMENTS);
				indices.push_back(i * NUM_SEGMENTS + (j + 1) % NUM_SEGMENTS);
			}
		}
	}

};

