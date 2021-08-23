#pragma once

#include "Entities.hpp"
#include "Shader.hpp"
#include "SpriteRenderer.hpp"
#include "BatchRenderer.hpp"
#include "TextureLoader.hpp"
#include <glm/glm.hpp>

class Pacman {
  private:
  private:
	TextureLoader tLoader;
	SpriteRenderer renderer;
	Maze maze;

  public:
	Pacman();
	void render() const noexcept;
};

Pacman::Pacman() : tLoader {}, renderer {{"old_shader.vert", "old_shader.frag"}} {
	tLoader.gl2DTexture("pacall.png", texType::DIFFUSE, "mainAtlas");
	tLoader.gl2DTexture("pactext.png", texType::DIFFUSE, "textAtlas");
	renderer.setResolution(224, 288);
	maze = Maze {SubTexture {tLoader.getTexture("mainAtlas"), {0, 0}, {224, 248}}};

}

void Pacman::render() const noexcept {
	renderer.drawSprite(maze.getSprite(), maze.getPos());
}
