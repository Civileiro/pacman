#pragma once

#include <GL/gl3w.h>

#include "Texture.hpp"
#include <glm/glm.hpp>
#include "Vertex.hpp"
#include "BatchRenderer.hpp"

class TileEntity {
  protected:
	SubTexture sTex;
	glm::vec2 pos {0.f};

  public:
	TileEntity() = default;
	TileEntity(const SubTexture &sTex) : sTex {sTex} {}
	SubTexture getSprite() const noexcept {
		return sTex;
	}
	glm::vec2 getPos() const noexcept {
		return pos;
	}
};

class BatchEntity : public TileEntity {
  protected:
	size_t bufferSize {};
	Vertex *buffer {nullptr};

  public:
	BatchEntity() = default;
	BatchEntity(const SubTexture &sTex, const size_t bufferSize) : TileEntity {sTex}, bufferSize {bufferSize} {}
	virtual void initBuffer() const noexcept {}
	virtual void updateBuffer() const noexcept {}

	friend void BatchRenderer::setBufferPointer(BatchEntity &entity) noexcept;
};

void BatchRenderer::setBufferPointer(BatchEntity &entity) noexcept {
	assert(entity.bufferSize + size <= bufferSize);
	entity.buffer = &vertexBuffer[size];
	size += entity.bufferSize;
	entity.initBuffer();
}

class Maze : public BatchEntity {
  private:
  public:
	Maze() = default;
	Maze(const SubTexture sTex) : BatchEntity {sTex, 4/* * 28 * 31 */} {}
	void updateBuffer() const noexcept {}
	void tick() noexcept {
		pos = {0.f, 16.f};
	}
  private:
	void initBuffer() const noexcept override {
		auto quad = Vertex::getQuad();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(pos, 0.0f));

		const glm::vec2 size {sTex.width, sTex.height};

		model = glm::scale(model, glm::vec3(size, 1.0f));

		for (auto &vert : quad) {
			vert.pos = model * glm::vec4 {vert.pos, 0.f, 1.f};
			vert.texPos = sTex.texTransform * glm::vec4 {vert.texPos, 0.f, 1.f};
			vert.texID = 0.f;
		}
		std::memcpy(buffer, &quad[0], bufferSize * sizeof(Vertex));
	}

};
