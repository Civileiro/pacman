#include "Engine.hpp"

Engine::Engine(unsigned ScrWidth, unsigned ScrHeight) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(ScrWidth, ScrHeight, "Pacman", NULL, NULL);
	if (!window) {
		throw std::exception {"ERROR::GLFW::FAILED_TO_CREATE_WINDOW"};
	}

	glfwMakeContextCurrent(window);

	glfwSetWindowUserPointer(window, this);

	if (gl3wInit()) {
		throw std::exception {"ERROR::GL3W::FAILED_TO_INIT_GL3W"};
	}
}
Engine::~Engine() {
	glfwTerminate();
}
bool Engine::shouldStayOpen() const noexcept {
	return !glfwWindowShouldClose(window);
}
int Engine::processInputs() const noexcept {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)

	// if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)

	// if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)

	// if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)

	return 0;
}
void Engine::swapBuffersAndPollEvents() const noexcept {
	glfwSwapBuffers(window);
	glfwPollEvents();
}
void Engine::setCallbacks() const noexcept {
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	});
}