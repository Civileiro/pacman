
#include "Main.hpp"

std::string Pacman::textureFolder {"src/textures"};
std::string Shader::shaderFolder {"src/shaders"};

int main() {
	try {

		const App app {672u, 864u};

		Pacman game {};

		const Shader spriteShader {"shader.vert", "shader.frag"};

		while (!glfwWindowShouldClose(app.getWindow())) {
			processInput(app.getWindow());

			glClearColor(0.5f, 1.f, 0.5f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(app.getWindow());
			glfwPollEvents();
		}
	} catch (std::exception e) {
		std::cout << e.what();
	}

	return 0;
}
