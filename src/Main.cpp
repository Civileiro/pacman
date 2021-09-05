
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
		screenRender.setResolution(672, 864);

		Pacman game {app.getWindow()};


		float deltaTime {0.f};
		float lastFrameTime {0.f};
		while (app.shouldStayOpen()) {
			float currentTime = (float) glfwGetTime();
			deltaTime = currentTime - lastFrameTime;
			lastFrameTime = currentTime;

			game.addTime(deltaTime);


			const auto pacTex = game.render()->getTex();

			app.bindDefaultFrameBuffer();

			glClearColor(0.1f, 0.1f, 0.1f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			screenRender.drawSprite(pacTex, {0.f, 0.f});

			app.swapBuffersAndPollEvents();
		}
	} catch (std::exception e) {
		std::cout << e.what();
	}

	return 0;
}
