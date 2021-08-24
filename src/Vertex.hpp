#pragma once

#include <glm/glm.hpp>

struct Vertex {
	glm::vec2 pos;
	glm::vec2 texPos;
	float texID;

	static constexpr std::array<Vertex, 4> getQuad() noexcept;
};

constexpr std::array<Vertex, 4> Vertex::getQuad() noexcept {
	std::array<Vertex, 4> quad {};
	quad[0].pos =		{0.f, 1.f};
	quad[0].texPos =	{0.f, 0.f};
	quad[0].texID =		{0.f};
	quad[1].pos =		{1.f, 1.f};
	quad[1].texPos =	{1.f, 0.f};
	quad[1].texID =		{0.f};
	quad[2].pos =		{1.f, 0.f};
	quad[2].texPos =	{1.f, 1.f};
	quad[2].texID =		{0.f};
	quad[3].pos =		{0.f, 0.f};
	quad[3].texPos =	{0.f, 1.f};
	quad[3].texID =		{0.f};
	return quad;
}
