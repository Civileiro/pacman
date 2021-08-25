#pragma once

#include "../../base_entities/BatchEntity.hpp"

class PacmanE : public BatchEntity {
  public:
	PacmanE() = default;
	PacmanE(const SubTexture sTex);

  private:
	void initBuffer() noexcept override;
};
