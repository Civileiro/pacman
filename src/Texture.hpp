#pragma once

#include <GL/gl3w.h>

enum class texType { NONE, DIFFUSE, SPECULAR };

struct Texture {
	GLuint ID;
	int width, height;
	texType type;
	Texture() = default;
	~Texture() {
		glDeleteTextures(1, &ID);
	}
	Texture(Texture &other) = delete;
};
