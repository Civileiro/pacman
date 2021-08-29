#pragma once

#include <GL/gl3w.h>

#include "../structs/Texture.hpp"
#include "../structs/Vertex.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include <memory>

class TileEntity {
  public:
	TileEntity() = default;
	TileEntity(glm::vec2 pos);
	[[nodiscard]] glm::vec2 getPos() const noexcept;

  protected:
	std::unique_ptr<SubTexture[]> sTextures ;
	glm::vec2 pos {0.f};
};







