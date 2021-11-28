#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>

using GLFWKey = decltype(GLFW_KEY_0);



enum class InputState { RELEASED, PRESSED, REPEAT };

class InputManager {
  public:
	InputManager(GLFWwindow *w);
	void bind(int input, GLFWKey key) noexcept;
	InputState getInputState(int input) const noexcept;

  private:
	GLFWwindow *window;
	std::unordered_map<int, GLFWKey> inputMapper;
};
