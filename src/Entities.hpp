#pragma once

#include <GL/gl3w.h>

#include "BatchRenderer.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"
#include <glm/glm.hpp>
#include <iostream>

class TileEntity {
  protected:
	SubTexture sTex {};
	glm::vec2 pos {0.f};

  public:
	TileEntity() = default;
	TileEntity(const SubTexture &sTex, glm::vec2 pos);
	SubTexture getSprite() const noexcept;
	glm::vec2 getPos() const noexcept;
};


class BatchEntity : public TileEntity {
  protected:
	size_t bufferSize {};
	Vertex *buffer {nullptr};

  public:
	BatchEntity() = default;
	BatchEntity(const SubTexture &sTex, const size_t bufferSize, glm::vec2 pos) : TileEntity {sTex, pos}, bufferSize {bufferSize} {}
	[[nodiscard]] virtual size_t getBufferSize() const noexcept {
		return bufferSize;
	};
	virtual void initBuffer() noexcept {}
	virtual void updateBuffer() const noexcept {}

	friend class BatchRenderer;
};



class Maze : public BatchEntity {
  private:
  public:
	Maze() = default;
	Maze(const SubTexture sTex) : BatchEntity {sTex, 4 /* * 28 * 31 */, {0.f, 16.f}} {}
	void updateBuffer() const noexcept {}
	void tick() noexcept {}

  private:
	void initBuffer() noexcept override{
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
		for (int i {0}; i < 4; i++) {
			std::cout << "quad: "<< quad[i].pos.x << " " << quad[i].pos.y << "\n";
		}
		std::memcpy(buffer, &quad[0], bufferSize * sizeof(Vertex));
	}
};

class PacmanE : public BatchEntity {
  public:
	PacmanE() = default;
	PacmanE(const SubTexture sTex) : BatchEntity {sTex, 4, {64.f, 64.f}} {}

  private:
	void initBuffer() noexcept override {
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
		//for (int i {0}; i < 4; i++) {
		//	std::cout << "pos" << i << " " << quad[i].pos.x << " " << quad[i].pos.y << "\n";
		//	std::cout << "tex" << i << " " << quad[i].texPos.x << " " << quad[i].texPos.y << "\n";
		//}
		std::memcpy(buffer, &quad[0], bufferSize * sizeof(Vertex));
	}
};
