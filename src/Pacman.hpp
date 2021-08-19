#pragma once

#include "Entities.hpp"
#include "TextureLoader.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>

class Pacman {
  private:
  private:
	static std::string textureFolder;
	Texture texAtlas;
	Texture texText;
	Maze maze;

  public:
	Pacman();
	void draw(Shader shader) const noexcept;
};

Pacman::Pacman()
    : texAtlas {TextureLoader::gl2DTexture(textureFolder + '/' + "pacall.png", texType::DIFFUSE)},
      texText {TextureLoader::gl2DTexture(textureFolder + '/' + "pactext.png", texType::DIFFUSE)},
      maze {&texAtlas} {
}

void Pacman::draw(Shader shader) const noexcept {
	shader.use();
	maze.draw(shader);
}
