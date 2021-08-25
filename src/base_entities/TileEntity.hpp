#pragma once

#include <GL/gl3w.h>

#include "../structs/Texture.hpp"
#include "../structs/Vertex.hpp"
#include <glm/glm.hpp>
#include <iostream>

class TileEntity {
  public:
	TileEntity() = default;
	TileEntity(const SubTexture &sTex, glm::vec2 pos);
	[[nodiscard]] SubTexture getSprite() const noexcept;
	[[nodiscard]] glm::vec2 getPos() const noexcept;

  protected:
	SubTexture sTex {};
	glm::vec2 pos {0.f};
};







