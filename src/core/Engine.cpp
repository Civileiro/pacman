#include "Engine.hpp"

std::string TextureManager::textureFolder {"textures/"};
std::string ShaderManager::shaderFolder {"shaders/"};

Engine::Engine() : core {800, 600}, pacman {core.getWindow()}, renderer {{"screenShader.vert", "screenShader.frag"}} {}

Engine::~Engine() = default;

void Engine::startEngine() {
	float deltaTime {0.f};
	float lastFrameTime {0.f};
	while (core.shouldStayOpen()) {
		float currentTime = (float) glfwGetTime();
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;
		gameLoop(deltaTime);
		frameLoop();
	}
}

void Engine::gameLoop(float frameTime) {
	pacman.addTime(frameTime);

}

void Engine::frameLoop() {
	const auto pacFrame = pacman.render()->getTex();

	core.bindDefaultFrameBuffer();

	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	renderer.drawSprite(pacFrame, {0.f, 0.f});

	core.swapBuffersAndPollEvents();
}