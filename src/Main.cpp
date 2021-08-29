
#include "core/Engine.hpp"
#include "game/Pacman.hpp"
#include "managers/TextureManager.hpp"
#include "managers/ShaderManager.hpp"

#include <iostream>
#include <string>


std::string TextureManager::textureFolder {"textures/"};
std::string ShaderManager::shaderFolder {"shaders/"};

int main() {
	try {

		const Engine app {672u, 864u};

		Pacman game {app.getWindow()};

		glClearColor(0.f, 0.f, 0.f, 1.f);

		float deltaTime {0.f};
		float lastFrameTime {0.f};
		while (app.shouldStayOpen()) {
			float currentTime = (float) glfwGetTime();
			deltaTime = currentTime - lastFrameTime;
			lastFrameTime = currentTime;


			
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
