#pragma once

#include "../../base_entities/BatchEntity.hpp"

class Maze : public BatchEntity {
  public:
	Maze() = default;
	Maze(const SubTexture sTex);
	void updateBuffer() const noexcept;
	void tick() noexcept;

  private:

};
