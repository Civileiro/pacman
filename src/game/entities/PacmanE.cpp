#include "PacmanE.hpp"

#include <cmath>
#include "PacEntities.hpp"

PacmanE::PacmanE(Texture *tex) : PacEntity {4, {112.f, 72.f}} {
	sTextures = std::vector<SubTexture>(20);

	const glm::vec2 texSize {16.f, 16.f};
	// clang-format off
	sTextures[RIGHT1]	= SubTexture {tex, {456.f + 0 * texSize.x, 248.f - 1 * texSize.y}, texSize};
	sTextures[RIGHT2]	= SubTexture {tex, {456.f + 1 * texSize.x, 248.f - 1 * texSize.y}, texSize};
	sTextures[LEFT1]	= SubTexture {tex, {456.f + 0 * texSize.x, 248.f - 2 * texSize.y}, texSize};
	sTextures[LEFT2]	= SubTexture {tex, {456.f + 1 * texSize.x, 248.f - 2 * texSize.y}, texSize};
	sTextures[UP1]		= SubTexture {tex, {456.f + 0 * texSize.x, 248.f - 3 * texSize.y}, texSize};
	sTextures[UP2]		= SubTexture {tex, {456.f + 1 * texSize.x, 248.f - 3 * texSize.y}, texSize};
	sTextures[DOWN1]	= SubTexture {tex, {456.f + 0 * texSize.x, 248.f - 4 * texSize.y}, texSize};
	sTextures[DOWN2]	= SubTexture {tex, {456.f + 1 * texSize.x, 248.f - 4 * texSize.y}, texSize};
	sTextures[START]	= SubTexture {tex, {456.f + 2 * texSize.x, 248.f - 1 * texSize.y}, texSize};
	sTextures[D1]		= SubTexture {tex, {456.f + 3 * texSize.x, 248.f - 1 * texSize.y}, texSize};
	sTextures[D2]		= SubTexture {tex, {456.f + 4 * texSize.x, 248.f - 1 * texSize.y}, texSize};
	sTextures[D3]		= SubTexture {tex, {456.f + 5 * texSize.x, 248.f - 1 * texSize.y}, texSize};
	sTextures[D4]		= SubTexture {tex, {456.f + 6 * texSize.x, 248.f - 1 * texSize.y}, texSize};
	sTextures[D5]		= SubTexture {tex, {456.f + 7 * texSize.x, 248.f - 1 * texSize.y}, texSize};
	sTextures[D6]		= SubTexture {tex, {456.f + 8 * texSize.x, 248.f - 1 * texSize.y}, texSize};
	sTextures[D7]		= SubTexture {tex, {456.f + 9 * texSize.x, 248.f - 1 * texSize.y}, texSize};
	sTextures[D8]		= SubTexture {tex, {456.f + 10* texSize.x, 248.f - 1 * texSize.y}, texSize};
	sTextures[D9]		= SubTexture {tex, {456.f + 11* texSize.x, 248.f - 1 * texSize.y}, texSize};
	sTextures[D10]		= SubTexture {tex, {456.f + 12* texSize.x, 248.f - 1 * texSize.y}, texSize};
	sTextures[D11]		= SubTexture {tex, {456.f + 13* texSize.x, 248.f - 1 * texSize.y}, texSize};
	// clang-format on
}
void PacmanE::updateBuffer() const noexcept {
	int useTex = currTex;
	if (animationStage == 0) {
		useTex = START;
	} else if ((animationStage == 1 || animationStage == 3) &&
			   (currTex == UP1 || currTex == RIGHT1 || currTex == DOWN1 || currTex == LEFT1)) {
		useTex += 1;
	}
	auto quad = Vertex::getQuad();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(pos.x - 8.f, pos.y - 8.f, 0.0f));

	const glm::vec2 size {sTextures[useTex].width, sTextures[useTex].height};

	model = glm::scale(model, glm::vec3(size, 1.0f));
	int i {0};
	for (auto &vert : quad) {
		vert.pos = model * glm::vec4 {vert.pos, 0.f, 1.f};
		vert.texPos = sTextures[useTex].texQuad[i++].texPos;
	}
	std::memcpy(buffer, &quad[0], bufferSize * sizeof(Vertex));
}

void PacmanE::tick(const PacVars &vars) noexcept {
	auto pacCanMove = vars.maze->canPacGo(currDir, pos);
	if (currDir == Direction::UP) {
		pos.y += velocity * pacCanMove;
		currTex = UP1;
	} else if (currDir == Direction::RIGHT) {
		pos.x += velocity * pacCanMove;
		currTex = RIGHT1;
	} else if (currDir == Direction::DOWN) {
		pos.y -= velocity * pacCanMove;
		currTex = DOWN1;
	} else if (currDir == Direction::LEFT) {
		pos.x -= velocity * pacCanMove;
		currTex = LEFT1;
	}
	if (pos.x < -8.f) {
		pos.x += 240.f;
	} else if (pos.x > 232.f) {
		pos.x -= 240.f;
	}
	std::cout << "pos:" << pos.x << '\t' << pos.y << '\n';
	auto mVec = pos - vars.pacman->pos;
	distanceMoved += abs(mVec.x) + abs(mVec.y);

	constexpr float distanceAnimation {3.f};
	distanceMoved = fmod(distanceMoved + 0.01f, distanceAnimation * 4) - 0.01f;
	animationStage = (distanceMoved + 0.01f) / distanceAnimation;
}

void PacmanE::goUp() noexcept {
	currDir = Direction::UP;
}
void PacmanE::goRight() noexcept {
	currDir = Direction::RIGHT;
}
void PacmanE::goDown() noexcept {
	currDir = Direction::DOWN;
}
void PacmanE::goLeft() noexcept {
	currDir = Direction::LEFT;
}
