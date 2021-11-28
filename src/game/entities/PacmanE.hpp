#pragma once

#include "PacEntity.hpp"
#include "../structs/Structs.hpp"

class PacmanE : public PacEntity {
  public:
	PacmanE() = default;
	PacmanE(Texture *);
	void updateBuffer() const noexcept;
	void tick(const PacVars &vars) noexcept;
	void goUp() noexcept;
	void goDown() noexcept;
	void goRight() noexcept;
	void goLeft() noexcept;

  private:
	enum { RIGHT1, RIGHT2, LEFT1, LEFT2, UP1, UP2, DOWN1, DOWN2, START, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11 };
	int currTex {START};
	Direction currDir {};
	float distanceMoved {0.f};
	float velocity {1.f};
	int animationStage {0};
};
