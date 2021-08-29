#include "InputManager.hpp"

InputManager::InputManager(GLFWwindow *w) : window {w} {}

void InputManager::bind(int input, GLFWKey key) noexcept {
	inputMapper[input] = key;
}


InputState InputManager::getInputState(int input) const noexcept {
	const auto state = glfwGetKey(window, inputMapper.find(input)->second);
	if (state == GLFW_PRESS) {
		return InputState::PRESSED;
	} 
	return InputState::RELEASED;
}
