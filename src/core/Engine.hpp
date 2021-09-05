#pragma once

#include "Core.hpp"
#include "../managers/TextureManager.hpp"
#include "../managers/ShaderManager.hpp"
#include "../game/Pacman.hpp"
#include "../renderers/SpriteRenderer.hpp"
#include "../core/wrappers/Framebuffer.hpp"



class Engine {
  public:
	Engine();
	~Engine();
	void startEngine();

  private:
	Core core;
	TextureManager texM;
	Pacman pacman;
	Framebuffer pacBuffer {224, 288};


	SpriteRenderer renderer;

	void gameLoop();
	void frameLoop();
};
