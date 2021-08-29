#pragma once

#include <GL/gl3w.h>

#include "../managers/InputManager.hpp"
#include "../managers/ShaderManager.hpp"
#include "../managers/TextureManager.hpp"
#include "../renderers/BatchRenderer.hpp"
#include "entities/PacEntities.hpp"
#include <algorithm>
#include <array>
#include <glm/glm.hpp>

class Pacman {
  public:
	Pacman(GLFWwindow *);
	void render() noexcept;
	void tick(float deltaTime) noexcept;

  private:
	GLFWwindow *window;
	TextureManager texManager;
	InputManager inputManager;
	BatchRenderer renderer;
	std::array<std::unique_ptr<BatchEntity>, 2> entities;

	enum {UP, DOWN, RIGHT, LEFT, PAUSE, BACK};

  private:
	void bindDefaults() noexcept;
};
