#include "Entities.hpp"

TileEntity::TileEntity(const SubTexture &sTex, glm::vec2 pos) : sTex {sTex}, pos {pos} {}

SubTexture TileEntity::getSprite() const noexcept {
	return sTex;
}

glm::vec2 TileEntity::getPos() const noexcept {
	return pos;
}

BatchEntity::BatchEntity(const SubTexture &sTex, const size_t bufferSize, glm::vec2 pos)
    : TileEntity {sTex, pos},
      bufferSize {bufferSize} {}

size_t BatchEntity::getBufferSize() const noexcept {
	return bufferSize;
}

void BatchEntity::initBuffer() noexcept {}
void BatchEntity::updateBuffer() const noexcept {}
