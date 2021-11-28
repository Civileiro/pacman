#include "PacVars.hpp"

#include "entities/PacEntities.hpp"

std::vector<BatchEntity *> PacVars::getEntityVector() noexcept {
	std::vector<BatchEntity *> vec;
	vec.push_back(reinterpret_cast<BatchEntity *>(maze.get()));
	vec.push_back(reinterpret_cast<BatchEntity *>(pacman.get()));

	return vec;
}

PacVars::PacVars(const PacVars& other) 
	: maze {std::make_unique<Maze>(*other.maze)},
	  pacman {std::make_unique<PacmanE>(*other.pacman)} {

}