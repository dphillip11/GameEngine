#pragma once
class BufferManager
{
public:
	static void setVertices(const void* vertices, int size, const int& VAO, const int& VBO);
	static void setIndices(const void* indices, int size, const int& EBO);
	static void setAttributes(int vaoPos, int count, GLenum type, bool normalized, int stride, const void* pos);
	static void Draw(int count, bool hasEBO, GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
	static void Bind(const int& VAO, const int& VBO, const int& EBO);
	static void Unbind();
};

