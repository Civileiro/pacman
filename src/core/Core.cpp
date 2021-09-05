#include "Core.hpp"

Core::Core(int scrWidth, int scrHeight) : scrWidth {scrWidth}, scrHeight {scrHeight} {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(scrWidth, scrHeight, "Pacman", NULL, NULL);
	if (!window) {
		throw std::exception {"ERROR::GLFW::FAILED_TO_CREATE_WINDOW"};
	}

	glfwMakeContextCurrent(window);

	glfwSetWindowUserPointer(window, this);

	if (gl3wInit()) {
		throw std::exception {"ERROR::GL3W::FAILED_TO_INIT_GL3W"};
	}

}
Core::~Core() {
	glfwTerminate();
}
bool Core::shouldStayOpen() const noexcept {
	return !glfwWindowShouldClose(window);
}

GLFWwindow *Core::getWindow() const noexcept {
	return window;
}

void Core::swapBuffersAndPollEvents() const noexcept {
	glfwSwapBuffers(window);
	glfwPollEvents();
}
void Core::setCallbacks() const noexcept {
	//glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
	//	glViewport(0, 0, width, height);
	//});
}

void Core::bindDefaultFrameBuffer() const noexcept {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
}
