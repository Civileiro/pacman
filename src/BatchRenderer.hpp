#pragma once

#include <GL/gl3w.h>

#include "Entities.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"
#include <algorithm>
#include <array>
#include <memory>
#include <vector>

class BatchEntity;

class BatchRenderer {
  private:
	GLuint VA, VB;
	Shader shader;
	int resWidth {224};
	int resHeight {288};
	size_t bufferSize;
	std::unique_ptr<Vertex[]> vertexBuffer;
	size_t size {};

  public:
	BatchRenderer(const Shader shader, size_t bufferSize);
	void setResolution(int width, int height) noexcept;
	void setBufferPointer(BatchEntity &entity) noexcept;
	void render() const noexcept;
	void clearBatch() noexcept {
		size = 0;
	}
};

inline BatchRenderer::BatchRenderer(const Shader shader, size_t bufferSize)
    : shader {shader},
      bufferSize {bufferSize},
      vertexBuffer {std::make_unique<Vertex[]>(bufferSize)} {

	shader.setIntVec("textures", std::array{0, 1});

	glGenVertexArrays(1, &VA);
	glGenBuffers(1, &VB);
	
	glBindVertexArray(VA);
	glBindBuffer(GL_ARRAY_BUFFER, VB);

	glBufferData(GL_ARRAY_BUFFER, bufferSize * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) (offsetof(Vertex, pos)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) (offsetof(Vertex, texPos)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) (offsetof(Vertex, texID)));

	size_t indexCount = gsl::narrow_cast<size_t>(std::ceil(bufferSize * 1.5f));

	auto indices = std::make_unique<GLuint[]>(indexCount);


	int offset {0};
	for (size_t i {0}; i < indexCount; i += 6) {
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;
		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}

	GLuint IB;
	glCreateBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indices.get(), GL_STATIC_DRAW);
}

inline void BatchRenderer::setResolution(int width, int height) noexcept {
	resWidth = width;
	resHeight = height;
}

inline void BatchRenderer::render() const noexcept {


	shader.use();

	const glm::mat4 proj {glm::ortho(0.f, (float) resWidth, 0.f, (float) resHeight)};
	shader.setMat4("projection", proj);

	int indexCount = gsl::narrow_cast<int>(std::ceil(size * 1.5f));
	glBindVertexArray(VA);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(Vertex), vertexBuffer.get());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
