#include "BatchEntity.hpp"

BatchEntity::BatchEntity(const SubTexture &sTex, const size_t bufferSize, glm::vec2 pos)
    : TileEntity {sTex, pos},
      bufferSize {bufferSize} {}

size_t BatchEntity::getBufferSize() const noexcept {
	return bufferSize;
}

void BatchEntity::initBuffer() noexcept {

	auto quad = Vertex::getQuad();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(pos, 0.0f));

	const glm::vec2 size {sTex.width, sTex.height};

	model = glm::scale(model, glm::vec3(size, 1.0f));

	for (auto &vert : quad) {
		vert.pos = model * glm::vec4 {vert.pos, 0.f, 1.f};
		vert.texPos = sTex.texTransform * glm::vec4 {vert.texPos, 0.f, 1.f};
		vert.texID = 0.f;
	}
	// for (int i {0}; i < 4; i++) {
	//	std::cout << "pos" << i << " " << quad[i].pos.x << " " << quad[i].pos.y << "\n";
	//	std::cout << "tex" << i << " " << quad[i].texPos.x << " " << quad[i].texPos.y << "\n";
	//}
	std::memcpy(buffer, &quad[0], bufferSize * sizeof(Vertex));
}
void BatchEntity::updateBuffer() const noexcept {}