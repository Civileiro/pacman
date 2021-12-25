#include <myEn/core/wrappers/Framebuffer.hpp>
#include <stdexcept>

Framebuffer::Framebuffer(int width, int height)
	: width {width},
	  height {height},
	  texBuffer {NULL, width, height, texType::DIFFUSE} {
	// glGenRenderbuffers(1, &RBO);
	// glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	// glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
	// glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glGenTextures(1, &texBuffer.ID);
	glBindTexture(GL_TEXTURE_2D, texBuffer.ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // REQUIRED!!!!!!!!!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // REQUIRED!!!!!!!!!

	glGenFramebuffers(1, &frameBufferObject);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texBuffer.ID, 0);
	// glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw std::runtime_error {"ERROR::FRAMEBUFFER:: Framebuffer is not complete!"};
}

Framebuffer::~Framebuffer() {
	glDeleteTextures(1, &texBuffer.ID);
	glDeleteFramebuffers(1, &frameBufferObject);
}

void Framebuffer::bind() const noexcept {
	glViewport(0, 0, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
}

void Framebuffer::bindRead() const noexcept {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBufferObject);
}

void Framebuffer::bindDraw() const noexcept {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferObject);
}

Texture *Framebuffer::getTex() noexcept {
	return &texBuffer;
}
