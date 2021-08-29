#pragma once

#include <GL/gl3w.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <gsl/gsl>
#include "Vertex.hpp"

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
	Texture *tex;
	int width, height;
	std::array<Vertex, 4> texQuad {Vertex::getQuad()};

	SubTexture() = default;
	SubTexture(Texture *texture, const glm::vec2 &coords, const glm::vec2 &size)
		: tex {texture},
		  width {gsl::narrow_cast<int>(size.x)},
		  height {gsl::narrow_cast<int>(size.y)} {
		glm::mat4 texTransform {1.f};
		texTransform = glm::translate(texTransform, glm::vec3(coords.x / texture->width, coords.y / texture->height, 0.f));
		texTransform = glm::scale(texTransform, glm::vec3 {size.x / texture->width, size.y / texture->height, 1.f});

		for (auto &vert : texQuad) {
			vert.texPos = texTransform * glm::vec4 {vert.texPos, 0.f, 1.f};
		}
	}
};