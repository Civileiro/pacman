#include "Engine.hpp"

#include <thread>

std::string TextureManager::textureFolder {"textures/"};
std::string ShaderManager::shaderFolder {"myEn/src/shaders/"};

Engine::Engine() {}

Engine::~Engine() = default;

void Engine::engineInit() {

	engineStart();

	float deltaTime {0.f};
	float lastFrameTime {0.f};
	while (core.shouldStayOpen()) {
		float currentTime = (float) glfwGetTime();
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		engineLoop(deltaTime);
	}
	engineClose();
}

