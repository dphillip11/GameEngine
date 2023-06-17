#pragma once
class BufferManager
{
public:
	static void setVertices(const std::vector<glm::vec3>& vertices, const int& VAO, const int& VBO);
	static void setIndices(const std::vector<int>& indices, const int& EBO);
	static void setAttributes(int vaoPos, int count, GLenum type, bool normalized, int stride, const void* pos);
	static void Draw(bool setEBO, int count, GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
	static void Bind(const int& VAO, const int& VBO, const int& EBO);
	static void Unbind();
};

