#pragma once

#include "Core.hpp"
#include "../managers/TextureManager.hpp"
#include "../managers/ShaderManager.hpp"
#include "../game/Pacman.hpp"
#include "../renderers/SpriteRenderer.hpp"

class Engine {
  public:
	Engine();
	~Engine();
	void startEngine();

  private:
	Core core;
	TextureManager texM;
	Pacman pacman;
	SpriteRenderer renderer;

	void gameLoop(float frameTime);
	void frameLoop();
};
