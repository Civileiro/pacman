#pragma once

#include "BatchRenderer.hpp"
#include "Entities.hpp"
#include "Shader.hpp"
#include "SpriteRenderer.hpp"
#include "TextureLoader.hpp"
#include <algorithm>
#include <array>
#include <glm/glm.hpp>

class Pacman {
  private:
  private:
	TextureLoader tLoader;
	BatchRenderer renderer;
	std::array<std::unique_ptr<BatchEntity>, 2> entities;

  public:
	Pacman();
	void render() noexcept;
	void tick(float deltaTime) noexcept;
};

Pacman::Pacman() : tLoader {}, renderer {} {
	tLoader.gl2DTexture("pacall.png", texType::DIFFUSE, "mainAtlas");
	tLoader.gl2DTexture("pactext.png", texType::DIFFUSE, "textAtlas");
	renderer.setResolution(224, 288);
	entities[0] = std::make_unique<Maze>(SubTexture {tLoader.getTexture("mainAtlas"), {0, 0}, {224, 248}});
	entities[1] = std::make_unique<PacmanE>(SubTexture {tLoader.getTexture("mainAtlas"), {456, 0}, {16, 16}});

	size_t totalBufferSize {0};
	auto addBuffers = [&totalBufferSize](const auto &ent) {
		totalBufferSize += ent->getBufferSize();
	};
	std::for_each(entities.begin(), entities.end(), addBuffers);
	renderer = BatchRenderer {{"shader.vert", "shader.frag"}, totalBufferSize};
	for (auto &ent : entities) {
		renderer.setBufferPointer(ent.get());
	}
}

void Pacman::render() noexcept {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tLoader.getTexture("mainAtlas").ID);
	renderer.render();
}

void Pacman::tick(float deltaTime) noexcept {}
