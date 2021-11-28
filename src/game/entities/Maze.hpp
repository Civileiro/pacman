#pragma once

#include "PacEntity.hpp"
#include "../structs/Structs.hpp"

class Maze : public PacEntity {
  public:
	Maze() = default;
	Maze(Texture *);
	void updateBuffer() const noexcept;
	void tick(const PacVars &vars) noexcept;
	void initBuffer() const noexcept;
	bool canPacGo(Direction dir, glm::vec2 pos) const noexcept;
	bool pacPassable(int num) const noexcept;

  private:
	int mazeInfo[31][28] {};
};
