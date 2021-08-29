#include "Pacman.hpp"

Pacman::Pacman(GLFWwindow *w) : window {w}, texManager {}, inputManager {w}, renderer {} {
	renderer.setResolution(224, 288);
	entities[0] = std::make_unique<Maze>(SubTexture {texManager.getTexture("pacMain.png"), {0, 0}, {224, 248}});
	entities[1] = std::make_unique<PacmanE>(SubTexture {texManager.getTexture("pacMain.png"), {456, 0}, {16, 16}});

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
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texManager.getTexture("pacMain.png")->ID);
	renderer.render();
}

void Pacman::addTime(float deltaTime) noexcept {
	constexpr auto fps = 60.f;

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

void Pacman::tick() noexcept {}
