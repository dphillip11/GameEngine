#include "PCH/pch.h"
#include "Managers/BufferManager.h"

void BufferManager::setVertices(const std::vector<glm::vec3>& vertices, const int& VAO, const int& VBO) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
}

void BufferManager::setIndices(const std::vector<int>& indices, const int& EBO) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
}

void BufferManager::setAttributes(int vaoPos, int count, GLenum type, bool normalized, int stride, const void* pos) {
	glEnableVertexAttribArray(vaoPos);
	glVertexAttribPointer(vaoPos, count, type, normalized ? GL_TRUE : GL_FALSE, stride, pos);
}

void BufferManager::Bind(const int& VAO, const int& VBO, const int& EBO) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void  BufferManager::Unbind() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void  BufferManager::Draw(bool setEBO, int count, GLenum fillMode, GLenum drawMode) {
	//can take draw mode GL_POINTS, GL_TRIANGLES and GL_LINE_STRIP
		//can take fill mode GL_LINE, GL_FILL
	glPolygonMode(GL_FRONT_AND_BACK, fillMode);
	if (setEBO)
	{
		glDrawElements(drawMode, count, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(drawMode, 0, count);
	}
	Unbind();
}
