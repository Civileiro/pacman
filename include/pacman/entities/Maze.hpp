#pragma once

#include "PacEntity.hpp"
#include "../structs/Structs.hpp"
#include <tuple>

class Maze : public PacEntity {
  public:
	Maze() = default;
	Maze(Texture *);
	void updateBuffer() noexcept;
	void initBuffer() noexcept;
	void tick(const PacVars &vars) noexcept;
	bool canPacGo(Direction dir, glm::vec2 pos) const noexcept;
	bool pacPassable(int num) const noexcept;
	std::tuple<int, int> currSquare(glm::vec2 pos) const noexcept;
	glm::vec2 currSquareMiddleCoords(glm::vec2 pos) const noexcept;
	bool isDepleted() const noexcept;
	void switchTile(std::size_t x, std::size_t y, bool switchSquare) noexcept;

  private:
	int mazeInfo[31][28] {};
	bool depletedGrid[31][28] {};
	bool depleted {false};
	std::size_t lastDepletedX, lastDepletedY;
	bool flashedTictac {false};
};