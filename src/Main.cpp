
#include "core/Engine.hpp"
#include "game/Pacman.hpp"
#include "managers/ShaderManager.hpp"
#include "managers/TextureManager.hpp"
#include "renderers/SpriteRenderer.hpp"

#include <iostream>
#include <string>

std::string TextureManager::textureFolder {"textures/"};
std::string ShaderManager::shaderFolder {"shaders/"};

int main() {
	try {

		const Engine app {672u, 864u};

		SpriteRenderer screenRender {{"screenShader.vert", "screenShader.frag"}};

		Pacman game {app.getWindow()};


		float deltaTime {0.f};
		float lastFrameTime {0.f};
		while (app.shouldStayOpen()) {
			float currentTime = (float) glfwGetTime();
			deltaTime = currentTime - lastFrameTime;
			lastFrameTime = currentTime;

			game.addTime(deltaTime);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, game.render().getTex());


			app.bindDefaultFrameBuffer();

			glClearColor(0.f, 0.1f, 0.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			screenRender.drawCurrentTextureToScreen();

			app.swapBuffersAndPollEvents();
		}
	} catch (std::exception e) {
		std::cout << e.what();
	}

	return 0;
}
