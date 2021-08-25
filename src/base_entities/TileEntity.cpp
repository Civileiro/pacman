#include "TileEntity.hpp"

TileEntity::TileEntity(const SubTexture &sTex, glm::vec2 pos) : sTex {sTex}, pos {pos} {}

SubTexture TileEntity::getSprite() const noexcept {
	return sTex;
}

glm::vec2 TileEntity::getPos() const noexcept {
	return pos;
}

