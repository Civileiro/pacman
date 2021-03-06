#pragma once
#include "TileEntity.hpp"

class BatchEntity : public TileEntity {
  public:
	BatchEntity() = default;
	BatchEntity(const size_t bufferSize, glm::vec2 pos);
	[[nodiscard]] virtual size_t getBufferSize() const noexcept;
	virtual void initBuffer() noexcept;
	virtual void updateBuffer() noexcept = 0;

	friend class BatchRenderer;

  protected:
	size_t bufferSize {};
	Vertex *buffer {nullptr};
};
