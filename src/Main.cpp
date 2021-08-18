
#include "App.hpp"
#include "Shader.hpp"

#include <iostream>

std::string Shader::shaderFolder {"src/shaders"};

int main() {

	const App app {640u, 480u};


	const Shader spriteShader {"shader.vert", "shader.frag"};

	while (!glfwWindowShouldClose(app.getWindow())) {
	}

	return 0;
}