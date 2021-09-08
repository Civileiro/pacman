#include "Engine.hpp"

#include <thread>

std::string TextureManager::textureFolder {"textures/"};
std::string ShaderManager::shaderFolder {"shaders/"};

Engine::Engine()
	: core {224 * 3, 288 * 3},
	  pacman {core.getWindow()},
	  renderer {{"screenShader.vert", "screenShader.frag"}} {}

Engine::~Engine() = default;

void Engine::startEngine() {

	gameLoop();
}

void Engine::gameLoop() {
	float deltaTime {0.f};
	float lastFrameTime {0.f};
	while (core.shouldStayOpen()) {
		float currentTime = (float) glfwGetTime();
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		pacman.addTime(deltaTime);

		frameLoop();
	}
}

void Engine::frameLoop() {
	pacBuffer.bind();
	pacman.render();

	core.bindDefaultFrameBuffer();

	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	int width, height;
	glfwGetWindowSize(core.getWindow(), &width, &height);
	renderer.setResolution(width, height);

	renderer.drawSpriteCenterScaled(pacBuffer.getTex());

	core.swapBuffersAndPollEvents();
}
