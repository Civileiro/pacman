#pragma once

#include <GL/gl3w.h>

#include "../renderers/BatchRenderer.hpp"
#include "../structs/Texture.hpp"
#include "../structs/Vertex.hpp"
#include <glm/glm.hpp>
#include <iostream>

class TileEntity {
  public:
	TileEntity() = default;
	TileEntity(const SubTexture &sTex, glm::vec2 pos);
	SubTexture getSprite() const noexcept;
	glm::vec2 getPos() const noexcept;

  protected:
	SubTexture sTex {};
	glm::vec2 pos {0.f};
};


class BatchEntity : public TileEntity {
  public:
	BatchEntity() = default;
	BatchEntity(const SubTexture &sTex, const size_t bufferSize, glm::vec2 pos);
	[[nodiscard]] virtual size_t getBufferSize() const noexcept;
	virtual void initBuffer() noexcept;
	virtual void updateBuffer() const noexcept;
	friend class BatchRenderer;

  protected:
	size_t bufferSize {};
	Vertex *buffer {nullptr};

};





