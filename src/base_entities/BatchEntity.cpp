#include "BatchEntity.hpp"

BatchEntity::BatchEntity(const SubTexture &sTex, const size_t bufferSize, glm::vec2 pos)
    : TileEntity {sTex, pos},
      bufferSize {bufferSize} {}

size_t BatchEntity::getBufferSize() const noexcept {
	return bufferSize;
}

void BatchEntity::initBuffer() noexcept {}
void BatchEntity::updateBuffer() const noexcept {}