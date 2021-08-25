#pragma once

#include "../renderers/BatchRenderer.hpp"
#include "entities/PacEntities.hpp"
#include "../managers/ShaderManager.hpp"
#include "../managers/TextureManager.hpp"
#include <algorithm>
#include <array>
#include <glm/glm.hpp>

class Pacman {
  public:
	Pacman();
	void render() noexcept;
	void tick(float deltaTime) noexcept;

  private:
	TextureManager texManager;
	BatchRenderer renderer;
	std::array<std::unique_ptr<BatchEntity>, 2> entities;
};
