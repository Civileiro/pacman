#include "framebuffer.hpp"
#include <exception>

Framebuffer::Framebuffer(int width, int height) : width {width}, height {height} {
	// glGenRenderbuffers(1, &RBO);
	// glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	// glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
	// glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // REQUIRED!!!!!!!!!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // REQUIRED!!!!!!!!!

	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &frameBufferObject);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
	// glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw std::exception {"ERROR::FRAMEBUFFER:: Framebuffer is not complete!"};

}

void Framebuffer::bind() const noexcept {
	glViewport(0, 0, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
}

GLuint Framebuffer::getTex() const noexcept {
	return texColorBuffer;
}
