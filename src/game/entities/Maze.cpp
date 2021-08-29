#include "Maze.hpp"

Maze::Maze(Texture *tex) : BatchEntity {4 /* * 28 * 31 */, {0.f, 16.f}} {
	sTextures.push_back(SubTexture {tex, {0.f, 0.f}, {224.f, 248.f}});
}

void Maze::updateBuffer() const noexcept {}

void Maze::tick() noexcept {}
