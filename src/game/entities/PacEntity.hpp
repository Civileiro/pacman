#pragma once

#include "src/base_entities/BatchEntity.hpp"
#include "../PacVars.hpp"


class PacEntity : public BatchEntity {
  public:
	PacEntity() = default;
	PacEntity(const size_t bufferSize, glm::vec2 pos) : BatchEntity {bufferSize, pos} {}
	virtual void tick(const PacVars &vars) noexcept = 0;
};
