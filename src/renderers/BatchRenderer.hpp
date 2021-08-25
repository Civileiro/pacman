#pragma once

#include <GL/gl3w.h>

#include "../base_entities/BatchEntity.hpp"
#include "../managers/ShaderManager.hpp"
#include "../structs/Vertex.hpp"
#include <algorithm>
#include <array>
#include <gsl/gsl>
#include <memory>
#include <vector>

class BatchEntity;

class BatchRenderer {
  public:
	BatchRenderer() = default;
	BatchRenderer(const ShaderManager shader, size_t bufferSize);
	void render() const noexcept;
	void setResolution(int width, int height) noexcept;
	void setBufferPointer(BatchEntity *entity) noexcept;
	void clearBatch() noexcept;

  private:
	GLuint VA, VB;
	ShaderManager shader;
	int resWidth {224};
	int resHeight {288};
	size_t bufferSize;
	std::unique_ptr<Vertex[]> vertexBuffer {};
	size_t size {};
};
