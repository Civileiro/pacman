#pragma once

#include <GL/gl3w.h>

#include "Texture.hpp"
#include <glm/glm.hpp>

class TileEntity {
  private:
	SubTexture sTex;
	glm::vec2 pos;

  public:
	TileEntity() = default;
	TileEntity(SubTexture sTex, glm::vec2 pos) : sTex {sTex}, pos {pos} {}
	SubTexture getSprite() const noexcept {
		return sTex;
	}
	glm::vec2 getPos() const noexcept {
		return pos;
	}
};

class Maze : public TileEntity {
  private:
  public:
	Maze() = default;
	Maze(SubTexture sTex) : TileEntity {sTex, glm::vec2{0.f, 16.f}} {}
};
