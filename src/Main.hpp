#pragma once

#include "App.hpp"
#include "Pacman.hpp"
#include "Shader.hpp"

#include <iostream>

void processInput(GLFWwindow *window) noexcept;

void processInput(GLFWwindow *window) noexcept {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)

	// if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)

	// if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)

	// if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
}