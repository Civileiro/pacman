#pragma once

#include "../managers/ShaderManager.hpp"
#include "../structs/Texture.hpp"

class SpriteRenderer {
  private:
	GLuint quadVAO;
	ShaderManager shader;
	int resWidth = 800;
	int resHeight = 600;

  public:
	SpriteRenderer(ShaderManager shader) noexcept;
	void setResolution(int width, int height) noexcept;
	void drawSprite(Texture texture, glm::vec2 position) const noexcept;
	void drawCurrentTextureToScreen() const noexcept;
	//void drawSprite(SubTexture texture, glm::vec2 position) const noexcept;
};
