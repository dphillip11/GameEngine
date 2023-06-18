#include "PCH/pch.h"
#include "Managers/BufferManager.h"

void BufferManager::setVertices(const void* vertices, int size, const int& VAO, const int& VBO) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
}
void BufferManager::setIndices(const void* indices, int size, const int& EBO) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(int), indices, GL_STATIC_DRAW);
}

void BufferManager::setAttributes(int vaoPos, int count, GLenum type, bool normalized, int stride, const void* pos)
{
	glEnableVertexAttribArray(vaoPos);
	glVertexAttribPointer(vaoPos, count, type, normalized ? GL_TRUE : GL_FALSE, stride, pos);
}

void BufferManager::Bind(const int& VAO, const int& VBO, const int& EBO) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void BufferManager::Unbind() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BufferManager::Draw(int count, bool hasEBO, GLenum fillMode, GLenum drawMode) {
	//can take draw mode GL_POINTS, GL_TRIANGLES and GL_LINE_STRIP
	//can take fill mode GL_LINE, GL_FILL
	glPolygonMode(GL_FRONT_AND_BACK, fillMode);
	if (hasEBO)
	{
		glDrawElements(drawMode, count, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(drawMode, 0, count);
	}
	Unbind();

}
