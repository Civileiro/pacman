#pragma once

#include <GL/gl3w.h>

#include <stb_image.h>

#include "Texture.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

class TextureLoader {
  private:
	static std::string textureFolder;
	std::unordered_map<std::string, Texture> loadedTextures;

  public:
	TextureLoader() = default;
	~TextureLoader() {
		for (auto &[texName, tex] : loadedTextures) {
			glDeleteTextures(1, &tex.ID);
		}
	}
	TextureLoader(const TextureLoader &other) = delete;
	TextureLoader &operator=(const TextureLoader &other) = delete;
	TextureLoader(TextureLoader &&other) = default;
	TextureLoader &operator=(TextureLoader &&other) = default;

	static Texture gl2DTexture(std::string fileName, texType type);
	Texture gl2DTexture(std::string fileName, texType type, std::string texName);

	Texture getTexture(std::string texName) noexcept {
		return loadedTextures[texName];
	}
};

Texture TextureLoader::gl2DTexture(std::string fileName, texType type) {

	auto path {textureFolder + '/' + fileName};
	GLuint textureID;
	glGenTextures(1, &textureID);

	// stbi_set_flip_vertically_on_load(true);

	int width, height, nrComponents;
	stbi_uc *data = stbi_load(path.data(), &width, &height, &nrComponents, 0);
	if (data) {

		GLenum internalFormat {GL_RGB};
		GLenum format {GL_RGB};
		if (type == texType::DIFFUSE) {
			if (nrComponents == 3) {
				format = GL_RGB;
				internalFormat = GL_SRGB;
			} else if (nrComponents == 4) {
				format = GL_RGBA;
				internalFormat = GL_SRGB_ALPHA;
			}
		} else {
			if (nrComponents == 3)
				format = internalFormat = GL_RGB;
			else if (nrComponents == 4)
				format = internalFormat = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);

	} else {
		throw std::exception {("Texture failed to load at path: " + path).c_str()};
	}
	stbi_image_free(data);

	return {textureID, width, height, type};
}

Texture TextureLoader::gl2DTexture(std::string fileName, texType type, std::string texName) {
	const Texture tex {gl2DTexture(fileName, type)};
	loadedTextures[texName] = tex;
	return tex;
}
