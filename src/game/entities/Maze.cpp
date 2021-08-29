#include "Maze.hpp"

Maze::Maze(const SubTexture sTex) : BatchEntity {sTex, 4 /* * 28 * 31 */, {0.f, 16.f}} {}

void Maze::updateBuffer() const noexcept {}

void Maze::tick() noexcept {}
