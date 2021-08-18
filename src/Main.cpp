
#include "App.hpp"
#include "Shader.hpp"

#include <iostream>

int main() {

	const App app {640u, 480u};

	const Shader spriteShader {"src/shaders/shader.vert", "src/shaders/shader.frag"};

	while (!glfwWindowShouldClose(app.getWindow())) {
	}

	return 0;
}