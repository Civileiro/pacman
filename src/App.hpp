#pragma once

#include <GL/gl3w.h>

#include <GLFW/glfw3.h>

#include <exception>

class App {
  private:
	GLFWwindow *window;

  public:
	App(unsigned ScrWidth, unsigned ScrHeight);
	~App();
	App(const App &other) = delete;

	auto getWindow() const noexcept;
};

App::App(unsigned ScrWidth, unsigned ScrHeight) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(ScrWidth, ScrHeight, "Pacman", NULL, NULL);
	if (!window) {
		throw std::exception {"ERROR::GLFW::FAILED_TO_CREATE_WINDOW"};
	}

	glfwMakeContextCurrent(window);

	if (gl3wInit()) {
		throw std::exception {"ERROR::GL3W::FAILED_TO_INIT_GL3W"};
	}
}
App::~App() {
	glfwTerminate();
}

auto App::getWindow() const noexcept {
	return window;
}