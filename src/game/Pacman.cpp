#include "Pacman.hpp"

Pacman::Pacman(GLFWwindow *w) : texManager {}, inputManager {w}, renderer {} {
	texManager.load2DTexture("pacall.png", texType::DIFFUSE, "mainAtlas");
	texManager.load2DTexture("pactext.png", texType::DIFFUSE, "textAtlas");
	renderer.setResolution(224, 288);
	entities[0] = std::make_unique<Maze>(SubTexture {texManager.getTexture("mainAtlas"), {0, 0}, {224, 248}});
	entities[1] = std::make_unique<PacmanE>(SubTexture {texManager.getTexture("mainAtlas"), {456, 0}, {16, 16}});

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
	glBindTexture(GL_TEXTURE_2D, texManager.getTexture("mainAtlas").ID);
	renderer.render();
}

void Pacman::tick(float deltaTime) noexcept {}

void Pacman::bindDefaults() noexcept {
	inputManager.bind(UP, GLFW_KEY_UP);
	inputManager.bind(DOWN, GLFW_KEY_DOWN);
	inputManager.bind(RIGHT, GLFW_KEY_RIGHT);
	inputManager.bind(LEFT, GLFW_KEY_LEFT);

}
