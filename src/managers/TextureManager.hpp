#pragma once

#include <GL/gl3w.h>

#include "../structs/Texture.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

class TextureManager {
  public:
	TextureManager() = default;
	~TextureManager();
	TextureManager(const TextureManager &other) = delete;
	TextureManager &operator=(const TextureManager &other) = delete;

	Texture getTexture(std::string texName) noexcept;

	static Texture load2DTexture(std::string fileName, texType type);
	Texture load2DTexture(std::string fileName, texType type, std::string texName);

  private:
	static std::string textureFolder;
	std::unordered_map<std::string, Texture> loadedTextures;

};

