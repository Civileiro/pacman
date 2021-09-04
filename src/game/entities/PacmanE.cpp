#include "PacmanE.hpp"

PacmanE::PacmanE(Texture *tex) : BatchEntity {4, {64.f, 64.f}} {
	sTextures = std::make_unique<SubTexture[]>(20);

	const glm::vec2 texSize {16.f, 16.f};
	// clang-format off
	sTextures[RIGHT1]	= SubTexture {tex, {456.f + 0 * texSize.x, 0.f + 0 * texSize.y}, texSize};
	sTextures[RIGHT2]	= SubTexture {tex, {456.f + 1 * texSize.x, 0.f + 0 * texSize.y}, texSize};
	sTextures[LEFT1]	= SubTexture {tex, {456.f + 0 * texSize.x, 0.f + 1 * texSize.y}, texSize};
	sTextures[LEFT2]	= SubTexture {tex, {456.f + 1 * texSize.x, 0.f + 1 * texSize.y}, texSize};
	sTextures[UP1]		= SubTexture {tex, {456.f + 0 * texSize.x, 0.f + 2 * texSize.y}, texSize};
	sTextures[UP2]		= SubTexture {tex, {456.f + 1 * texSize.x, 0.f + 2 * texSize.y}, texSize};
	sTextures[DOWN1]	= SubTexture {tex, {456.f + 0 * texSize.x, 0.f + 3 * texSize.y}, texSize};
	sTextures[DOWN2]	= SubTexture {tex, {456.f + 1 * texSize.x, 0.f + 3 * texSize.y}, texSize};
	sTextures[START]	= SubTexture {tex, {456.f + 2 * texSize.x, 0.f + 0 * texSize.y}, texSize};
	sTextures[D1]		= SubTexture {tex, {456.f + 3 * texSize.x, 0.f + 0 * texSize.y}, texSize};
	sTextures[D2]		= SubTexture {tex, {456.f + 4 * texSize.x, 0.f + 0 * texSize.y}, texSize};
	sTextures[D3]		= SubTexture {tex, {456.f + 5 * texSize.x, 0.f + 0 * texSize.y}, texSize};
	sTextures[D4]		= SubTexture {tex, {456.f + 6 * texSize.x, 0.f + 0 * texSize.y}, texSize};
	sTextures[D5]		= SubTexture {tex, {456.f + 7 * texSize.x, 0.f + 0 * texSize.y}, texSize};
	sTextures[D6]		= SubTexture {tex, {456.f + 8 * texSize.x, 0.f + 0 * texSize.y}, texSize};
	sTextures[D7]		= SubTexture {tex, {456.f + 9 * texSize.x, 0.f + 0 * texSize.y}, texSize};
	sTextures[D8]		= SubTexture {tex, {456.f + 10* texSize.x, 0.f + 0 * texSize.y}, texSize};
	sTextures[D9]		= SubTexture {tex, {456.f + 11* texSize.x, 0.f + 0 * texSize.y}, texSize};
	sTextures[D10]		= SubTexture {tex, {456.f + 12* texSize.x, 0.f + 0 * texSize.y}, texSize};
	sTextures[D11]		= SubTexture {tex, {456.f + 13* texSize.x, 0.f + 0 * texSize.y}, texSize};
	// clang-format on
}

void PacmanE::tick() noexcept {
	if (currentTex != RIGHT1) {
		currentTex = RIGHT1;
	} else {
		currentTex = RIGHT2;
	}
	updateBuffer();

}

void PacmanE::updateBuffer() const noexcept {
	int i {0};
	for (auto &texVert : sTextures[currentTex].texQuad) {
		buffer[i++].texPos = texVert.texPos;
	}
}
