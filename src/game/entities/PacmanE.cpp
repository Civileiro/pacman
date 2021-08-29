#include "PacmanE.hpp"


PacmanE::PacmanE(Texture *tex) : BatchEntity {4, {64.f, 64.f}} {
	sTextures = std::make_unique<SubTexture[]>(20);

	const glm::vec2 texSize {16.f, 16.f};
	sTextures[0] = SubTexture {tex, {456.f, 0.f}, texSize};
}


