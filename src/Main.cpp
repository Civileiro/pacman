
#include "Main.hpp"

std::string TextureLoader::textureFolder {"textures"};
std::string Shader::shaderFolder {"shaders"};

int main() {
	try {

		const Engine app {672u, 864u};

		Pacman game {};


		while (app.shouldStayOpen()) {
			app.processInputs();

			glClearColor(0.5f, 1.f, 0.5f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			game.render();

			app.swapBuffersAndPollEvents();
		}
	} catch (std::exception e) {
		std::cout << e.what();
	}

	return 0;
}
