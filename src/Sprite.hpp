#pragma once

#include <GL/gl3w.h>

#include "Shader.hpp"
#include "Texture.hpp"
#include <array>
#include <glm/glm.hpp>
#include <gsl/gsl>
#include <iostream>

struct Sprite {
  private:
	GLuint VAO, VBO, EBO;
	std::array<glm::vec2, 4> texCoords;
	Texture *texture;
	float width, height;

  public:
	Sprite(Texture *tex, glm::vec2 topLeftCoords, glm::vec2 bottomRightCoords);
	void setupQuad() const noexcept;
	void draw(Shader shader) const noexcept;
	std::tuple<float, float> getWidthHeight() const noexcept;
	void setTexture(Texture *tex) noexcept;
};

Sprite::Sprite(Texture *tex, glm::vec2 topLeftCoords, glm::vec2 bottomRightCoords)
    : texture {tex},
      width {(bottomRightCoords.x - topLeftCoords.x) * tex->width},
      height {(bottomRightCoords.y - topLeftCoords.y) * tex->height},
      texCoords {glm::vec2 {topLeftCoords}, glm::vec2 {bottomRightCoords.x, topLeftCoords.y}, glm::vec2 {bottomRightCoords},
		 glm::vec2 {topLeftCoords.x, bottomRightCoords.y}} {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	setupQuad();
}
void Sprite::setupQuad() const noexcept {

	auto pacmanWidth = 224u;
	auto pacmanHeight = 288u;
	auto fixRatio = [](float i) {
		return (i * 2) - 1;
	};
	float vert[] {
	    -1.f,							1.f,								texCoords[0].x, texCoords[0].y,
	    fixRatio(width / pacmanWidth),	1.f,								texCoords[1].x, texCoords[1].y, 
		fixRatio(width / pacmanWidth),	fixRatio(height / pacmanHeight),	texCoords[2].x, texCoords[2].y, 
		-1.f,							fixRatio(height / pacmanHeight),	texCoords[3].x, texCoords[3].y,
	};
	std::cout << height << " " << width;

	unsigned int ind[] {0, 1, 2, 2, 3, 0};

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), &vert[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), &ind[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) (2 * sizeof(float)));

	glBindVertexArray(0);
}

void Sprite::draw(Shader shader) const noexcept {
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, texture->ID);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

std::tuple<float, float> Sprite::getWidthHeight() const noexcept {
	return {width, height};
}

void Sprite::setTexture(Texture *tex) noexcept {
	texture = tex;
}
