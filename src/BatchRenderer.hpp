#pragma once

#include <GL/gl3w.h>

#include "Shader.hpp"
#include "Vertex.hpp"
#include <vector>

template <size_t vertexArraySize>
class BatchRenderer {
  private:
	GLuint quadVA;
	Shader shader;
	std::vector<Vertex> vertexes {vertexArraySize};

  public:
	BatchRenderer(const Shader shader);
};

template <size_t vertexArraySize>
inline BatchRenderer<vertexArraySize>::BatchRenderer(const Shader shader) : shader {shader} {

	glGenVertexArrays(1, &quadVA);

	glBindVertexArray(quadVA);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) (offsetof(Vertex, pos)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) (offsetof(Vertex, texPos)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) (offsetof(Vertex, texID)));

	glBindVertexArray(0);
}
