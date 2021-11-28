#pragma once

#include <GL/gl3w.h>

#include "src/managers/InputManager.hpp"
#include "src/managers/ShaderManager.hpp"
#include "src/managers/TextureManager.hpp"
#include "src/renderers/BatchRenderer.hpp"
#include "src/core/Engine.hpp"
#include "entities/PacEntities.hpp"
#include "PacVars.hpp"

#include <algorithm>
#include <vector>
#include <glm/glm.hpp>


class Pacman : public Engine {
  public:
	Pacman();

  private:
	virtual void engineStart();
	virtual void engineLoop(float frameDelta);
	virtual void engineClose();

	

	TextureManager texManager;
	InputManager inputManager;
	BatchRenderer renderer;
	PacVars vars;

	enum {UP, DOWN, RIGHT, LEFT, PAUSE, BACK, EXIT};

	void bindDefaultKeys() noexcept;
	void tick() noexcept;
	void render() noexcept;
	void processInputs() noexcept;
};
