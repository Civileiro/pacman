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
	BatchRenderer renderer;
	Maze maze;

  public:
	Pacman();
	void render() noexcept;
	void tick(float deltaTime) noexcept;
};

Pacman::Pacman() : tLoader {}, renderer {{"shader.vert", "shader.frag"}, 4} {
	tLoader.gl2DTexture("pacall.png", texType::DIFFUSE, "mainAtlas");
	tLoader.gl2DTexture("pactext.png", texType::DIFFUSE, "textAtlas");
	renderer.setResolution(224, 288);
	maze = Maze {SubTexture {tLoader.getTexture("mainAtlas"), {0, 0}, {224, 248}}};
	renderer.setBufferPointer(maze);

}

void Pacman::render() noexcept {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tLoader.getTexture("mainAtlas").ID);
	renderer.render();
}

void Pacman::tick(float deltaTime) noexcept {
	maze.tick();
}
