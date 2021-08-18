#pragma once

#include "TextureLoader.hpp"

class Pacman {
  private:
	static std::string textureFolder;
	GLuint atlas;
	GLuint text;

  public:
	Pacman();
};

Pacman::Pacman() {
	atlas = TextureLoader::gl2DTexture(textureFolder + '/' + "pacall.png", texType::DIFFUSE);
	text = TextureLoader::gl2DTexture(textureFolder + '/' + "pactext.png", texType::DIFFUSE);
}
