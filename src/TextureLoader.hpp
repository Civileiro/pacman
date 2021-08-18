#pragma once

#include <GL/gl3w.h>

#include <stb_image.h>

#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

enum class texType { NONE, DIFFUSE, SPECULAR };

class TextureLoader {
  private:
  public:
	[[nodiscard]] static GLuint gl2DTexture(std::string path, texType type);
};

GLuint TextureLoader::gl2DTexture(std::string path, texType type) {


	GLuint textureID;
	glGenTextures(1, &textureID);

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

	return textureID;
}
