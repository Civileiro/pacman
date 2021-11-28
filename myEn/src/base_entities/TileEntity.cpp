#include "TileEntity.hpp"

TileEntity::TileEntity(glm::vec2 pos) : pos {pos} {}


glm::vec2 TileEntity::getPos() const noexcept {
	return pos;
}

