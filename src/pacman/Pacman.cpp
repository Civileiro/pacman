#include <pacman/Pacman.hpp>

constexpr int pacmanWidth {224};
constexpr int pacmanHeight {288};

Pacman::Pacman() : inputManager {core.getWindow()} {}

void Pacman::engineStart() {

	bindDefaultKeys();

	core.setWindowSize(pacmanWidth * 3, pacmanHeight * 3);
	vars.maze = std::make_unique<Maze>(texManager.getTexture("pacMain.png"));
	vars.pacman = std::make_unique<PacmanE>(texManager.getTexture("pacMain.png"));

	auto entities = vars.getEntityVector();

	size_t totalBufferSize {0};
	auto addBuffers = [&totalBufferSize](const auto &ent) {
		totalBufferSize += ent->getBufferSize();
	};
	std::for_each(entities.begin(), entities.end(), addBuffers);

	renderer = BatchRenderer {{"shader.vert", "shader.frag"}, totalBufferSize};
	renderer.setResolution(pacmanWidth, pacmanHeight);
	for (auto &ent : entities) {
		renderer.setBufferPointer(ent);
	}


}
void Pacman::engineLoop(float frameDelta) {

	constexpr auto fps = 60.f;

	static float timeBucket {};
	timeBucket += frameDelta;
	while (timeBucket > 1.f / fps) {
		tick();
		timeBucket -= 1.f / fps;
	}

	render();

	core.swapBuffersAndPollEvents();
}
void Pacman::engineClose() {}

void Pacman::render() noexcept {
	core.bindDefaultFrameBuffer();

	glClearColor(1.f / 255.f, 1.f / 255.f, 1.f / 255.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texManager.getTexture("pacMain.png")->ID);

	renderer.render();

}


void Pacman::bindDefaultKeys() noexcept {
	inputManager.bind(UP, GLFW_KEY_UP);
	inputManager.bind(DOWN, GLFW_KEY_DOWN);
	inputManager.bind(RIGHT, GLFW_KEY_RIGHT);
	inputManager.bind(LEFT, GLFW_KEY_LEFT);
	inputManager.bind(EXIT, GLFW_KEY_ESCAPE);
}

void Pacman::tick() noexcept {
	processInputs();

	const auto oldVars = vars;
	vars.pacman->tick(oldVars);
	vars.maze->tick(oldVars);

	auto entities = vars.getEntityVector();
	for (auto ent : entities) {
		ent->updateBuffer();
	}
	vars.time++;
}

void Pacman::processInputs() noexcept {
	if (inputManager.getInputState(UP) == InputState::PRESSED) {
		vars.pacman->goDir(Direction::UP, vars);
	} else if (inputManager.getInputState(RIGHT) == InputState::PRESSED) {
		vars.pacman->goDir(Direction::RIGHT, vars);
	} else if (inputManager.getInputState(DOWN) == InputState::PRESSED) {
		vars.pacman->goDir(Direction::DOWN, vars);
	} else if (inputManager.getInputState(LEFT) == InputState::PRESSED) {
		vars.pacman->goDir(Direction::LEFT, vars);
	}
	if (inputManager.getInputState(EXIT) == InputState::PRESSED) {
		exit(0);
	}
}