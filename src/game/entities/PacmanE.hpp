#pragma once

#include "../../base_entities/BatchEntity.hpp"

class PacmanE : public BatchEntity {
  public:
	PacmanE() = default;
	PacmanE(Texture *);
	void tick() noexcept;
	void updateBuffer() const noexcept;

  private:
	enum { RIGHT1, RIGHT2, LEFT1, LEFT2, UP1, UP2, DOWN1, DOWN2, START, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11 };
	int currentTex {START};
};
