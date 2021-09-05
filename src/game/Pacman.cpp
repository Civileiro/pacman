#include "Pacman.hpp"

Pacman::Pacman(GLFWwindow *w) : window {w}, texManager {}, inputManager {w}, renderer {} {
	renderer.setResolution(224, 288);
	entities.reserve(2);
	entities.emplace_back( std::make_unique<Maze>(texManager.getTexture("pacMain.png")));
	entities.emplace_back(std::make_unique<PacmanE>(texManager.getTexture("pacMain.png")));

	size_t totalBufferSize {0};
	auto addBuffers = [&totalBufferSize](const auto &ent) {
		totalBufferSize += ent->getBufferSize();
	};
	std::for_each(entities.begin(), entities.end(), addBuffers);
	renderer = BatchRenderer {{"shader.vert", "shader.frag"}, totalBufferSize};
	for (auto &ent : entities) {
		renderer.setBufferPointer(ent.get());
	}

	bindDefaults();
}

void Pacman::render() noexcept {

	glClearColor(1.f / 255.f, 1.f / 255.f, 1.f / 255.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texManager.getTexture("pacMain.png")->ID);
	changeBuffer.lock();
	renderer.render();
	changeBuffer.unlock();


}

void Pacman::addTime(float deltaTime) noexcept {
	constexpr auto fps = 1.f;

	timeBucket += deltaTime;
	while (timeBucket > 1.f / fps) {
		tick();
		timeBucket -= 1.f / fps;
	}
}

void Pacman::bindDefaults() noexcept {
	inputManager.bind(UP, GLFW_KEY_UP);
	inputManager.bind(DOWN, GLFW_KEY_DOWN);
	inputManager.bind(RIGHT, GLFW_KEY_RIGHT);
	inputManager.bind(LEFT, GLFW_KEY_LEFT);

}

void Pacman::tick() noexcept {
	entities[1]->tick();

	changeBuffer.lock();
	entities[1]->updateBuffer();
	changeBuffer.unlock();

}
