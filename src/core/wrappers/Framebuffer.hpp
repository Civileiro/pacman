#pragma once

#include <GL/gl3w.h>

class Framebuffer {
  public:
	Framebuffer(int width, int height);
	void bind() const noexcept;
	GLuint getTex() const noexcept;
  private:
	int width, height;
	GLuint frameBufferObject;
	GLuint texColorBuffer;
};
