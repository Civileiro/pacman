
#include "Main.hpp"

std::string TextureLoader::textureFolder {"textures"};
std::string Shader::shaderFolder {"shaders"};

int main() {
	try {

		const Engine app {672u, 864u};

		Pacman game {};

		float deltaTime {0.f};
		float lastFrameTime {0.f};
		while (app.shouldStayOpen()) {
			float currentTime = (float) glfwGetTime();
			deltaTime = currentTime - lastFrameTime;
			lastFrameTime = currentTime;

			app.processInputs();

			glClearColor(0.5f, 1.f, 0.5f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			game.tick(deltaTime);

			game.render();

			app.swapBuffersAndPollEvents();
		}
	} catch (std::exception e) {
		std::cout << e.what();
	}

	return 0;
}
