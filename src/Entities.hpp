#pragma once

#include <GL/gl3w.h>

#include "Sprite.hpp"
#include "Texture.hpp"
#include <glm/glm.hpp>

struct TileEntity {
  private:
	Sprite sprite;

  public:
	TileEntity(Texture *tex, glm::vec2 topLeftCoords, glm::vec2 bottomRightCoords) : sprite {tex, topLeftCoords, bottomRightCoords} {}
	void draw(Shader shader) const noexcept {
		sprite.draw(shader);
	}
};

struct Maze : public TileEntity {

	Maze(Texture *tex) : TileEntity {tex, {0, 0}, {224.f / tex->width, 1.f}} {}
};
