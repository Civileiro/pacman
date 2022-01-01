#include <myEn/renderers/SpriteRenderer.hpp>

SpriteRenderer::SpriteRenderer(ShaderManager shader) noexcept : shader {shader} {

	setResolution(resWidth, resHeight);

	shader.setInt("tex", 0);

	GLuint VBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &VBO);

	// clang-format off
	constexpr float vertices[] = { 
        // pos      // tex
	    0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
    };

	// clang-format on
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) (2 * sizeof(float)));

	glBindVertexArray(0);
}

void SpriteRenderer::setResolution(int width, int height) noexcept {
	resWidth = width;
	resHeight = height;
}

void SpriteRenderer::drawSprite(Texture *texture, glm::vec2 position, float scaler) const noexcept {
	// prepare transformations
	this->shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	const glm::vec2 size {texture->width, texture->height};

	model = glm::scale(model, glm::vec3(size * scaler, 1.0f));

	this->shader.setMat4("model", model);

	const glm::mat4 proj {glm::ortho(0.f, (float) resWidth, 0.f, (float) resHeight)};

	shader.setMat4("projection", proj);

	constexpr auto texTrans {glm::mat4 {1.f}};
	this->shader.setMat4("texTransform", texTrans);

	glActiveTexture(GL_TEXTURE0);
	texture->bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void SpriteRenderer::drawSpriteCenterScaled(Texture *texture) const noexcept {
	const auto ratioTex {(float) texture->height / (float) texture->width};
	const auto ratioScr {(float) resHeight / (float) resWidth};
	float scaler;
	glm::vec2 pos {};
	if (ratioTex > ratioScr) {
		scaler = (float) resHeight / (float) texture->height;
		pos = {(float) (resWidth - texture->width * scaler) / 2.f, 0.f};
	} else {
		scaler = (float) resWidth / (float) texture->width;
		pos = {0.f, (float) (resHeight - texture->height * scaler) / 2.f};
	}
	drawSprite(texture, pos, scaler);
}

// void SpriteRenderer::drawSprite(SubTexture subTexture, glm::vec2 position) const noexcept {
//	// prepare transformations
//	this->shader.use();
//
//	glm::mat4 model = glm::mat4(1.0f);
//	model = glm::translate(model, glm::vec3(position, 0.0f));
//
//	const glm::vec2 size {subTexture.width, subTexture.height};
//
//	model = glm::scale(model, glm::vec3(size, 1.0f));
//
//	this->shader.setMat4("model", model);
//
//	const glm::mat4 proj {glm::ortho(0.f, (float) resWidth, 0.f, (float) resHeight)};
//	shader.setMat4("projection", proj);
//
//	this->shader.setMat4("texTransform", subTexture.texTransform);
//
//	glActiveTexture(GL_TEXTURE0);
//	subTexture.tex.bind();
//
//	glBindVertexArray(this->quadVAO);
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//	glBindVertexArray(0);
//}
