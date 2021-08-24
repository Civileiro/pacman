#pragma once

#include "Entities.hpp"

class Maze : public BatchEntity {
  public:
	Maze() = default;
	Maze(const SubTexture sTex);
	void updateBuffer() const noexcept;
	void tick() noexcept;

  private:
	void initBuffer() noexcept override;
};
