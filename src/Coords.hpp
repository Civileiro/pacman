#pragma once

#include <cmath>

struct Coords {
  public:
	int x, y;
	[[nodiscard]] constexpr float distanceTo(Coords other) const noexcept;
};

/*
     IMPLEMENTATION
*/

constexpr float Coords::distanceTo(Coords other) const noexcept {
	const auto deltaX = x - other.x;
	const auto deltaY = y - other.y;
	return sqrt((deltaX * deltaX) + (deltaY * deltaY));
}