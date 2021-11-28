#pragma once

#include "../core/wrappers/Framebuffer.hpp"
#include "../managers/ShaderManager.hpp"
#include "../managers/TextureManager.hpp"
#include "../renderers/SpriteRenderer.hpp"
#include "Core.hpp"

class Engine {
  public:
	Engine();
	~Engine();
	void engineInit();

  protected:
	virtual void engineStart() = 0;
	virtual void engineLoop(float frameDelta) = 0;
	virtual void engineClose() = 0;

	Core core;
};
