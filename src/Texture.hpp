#pragma once

#include <GL/gl3w.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <gsl/gsl>

enum class texType { NONE, DIFFUSE, SPECULAR };

struct Texture {
	GLuint ID;
	int width, height;
	texType type;

	void bind() const noexcept {
		glBindTexture(GL_TEXTURE_2D, ID);
	}
};

struct SubTexture {
	Texture tex;
	int width, height;
	glm::mat4 texTransform;

	SubTexture() = default;
	SubTexture(const Texture &texture, const glm::vec2 &coords, const glm::vec2 &size)
	    : tex {texture},
	      width {gsl::narrow_cast<int>(size.x)},
	      height {gsl::narrow_cast<int>(size.y)},
	      texTransform {1.f} {

		texTransform = glm::translate(texTransform, glm::vec3(coords, 0.f));
		texTransform = glm::scale(texTransform, glm::vec3 {size.x / texture.width, size.y / texture.height, 1.f});
	}
};