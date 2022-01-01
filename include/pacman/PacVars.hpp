#pragma once

#include <vector>
#include <memory>
#include <myEn/base_entities/BatchEntity.hpp>

class Maze;
class PacmanE;

struct PacVars {
	uint64_t time {0}; 
	std::unique_ptr<Maze> maze;
	std::unique_ptr <PacmanE> pacman;

	PacVars() = default;
	PacVars(const PacVars &other);
	std::vector<BatchEntity *> getEntityVector() noexcept;
};