#pragma once

#include <GL/gl3w.h>

#include "../../structs/Texture.hpp"

class Framebuffer {
  public:
	Framebuffer(int width, int height);
	~Framebuffer();
	Framebuffer(const Framebuffer &other) = delete;
	Framebuffer &operator=(const Framebuffer &other) = delete;
	void bind() const noexcept;
	Texture *getTex() noexcept;
  private:
	int width, height;
	GLuint frameBufferObject;
	Texture texBuffer;
};
