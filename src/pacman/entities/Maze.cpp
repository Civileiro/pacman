#include <pacman/entities/Maze.hpp>
#include <pacman/entities/PacEntities.hpp>

#include <cmath>
#include <gsl/gsl>
// clang-format off
Maze::Maze(Texture *tex) 
	: PacEntity {4 * 28 * 31, {0.f, 16.f}}, 
	mazeInfo			{	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
							{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, },
							{0, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 3, 0, },
							{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, },
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
							{0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, },
							{0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, },
							{0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, },
							{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, },
							{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, },
							{0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 2, 2, 8, 2, 2, 8, 2, 2, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, },
							{0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 7, 7, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, },
							{0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 9, 9, 9, 9, 9, 9, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, },
							{9, 9, 9, 9, 9, 9, 1, 2, 2, 2, 0, 9, 9, 9, 9, 9, 9, 0, 2, 2, 2, 1, 9, 9, 9, 9, 9, 9, },
							{0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 9, 9, 9, 9, 9, 9, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, },
							{0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, },
							{0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, },
							{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, },
							{0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, },
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
							{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, },
							{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, },
							{0, 3, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 6, 2, 2, 6, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 3, 0, },
							{0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, },
							{0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, },
							{0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, },
							{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, },
							{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, },
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
							{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },} 
{
	sTextures = std::vector<SubTexture>(28 * 31);
	// sTextures[0] = SubTexture {tex, {0.f, 0.f}, {224.f, 248.f}};
	for (size_t y {0}; y < 31; y++) {
		for (size_t x {0}; x < 28; x++) {
			const float posX {x * 8.f};
			const float posY {y * 8.f};

			sTextures[x + y * 28] = SubTexture {tex, {posX, posY}, {8.f, 8.f}};
		}
	}
}
// clang-format on


void Maze::initBuffer() noexcept {

	for (size_t y {0}; y < 31; y++) {
		for (size_t x {0}; x < 28; x++) {
			const auto index = x + (y * 28);

			auto *buf {&buffer[index * 4]};
			auto quad {Vertex::getQuad()};
			std::memcpy(buf, &quad[0], sizeof(Vertex));

			const float posX {x * 8.f};
			const float posY {y * 8.f};

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(pos.x + posX, pos.y + posY, 0.0f));

			const glm::vec2 size {sTextures[index].width, sTextures[index].height};

			model = glm::scale(model, glm::vec3(size, 1.0f));
			int i {0};
			for (auto &vert : quad) {
				buf[i].pos = model * glm::vec4 {vert.pos, 0.f, 1.f};
				buf[i].texPos = sTextures[index].texQuad[i].texPos;
				buf[i].texID = 0.f;
				i++;
			}
		}
	}
}
void Maze::updateBuffer() noexcept {
	if (depleted) {
		switchTile(lastDepletedX, lastDepletedY, true);
	}
	for (size_t y {0}; y < 31; y++) {
		for (size_t x {0}; x < 28; x++) {
			const auto inY = 30 - y;
			if (mazeInfo[inY][x] != 3 || depletedGrid[inY][x]) {
				continue;
			}
			switchTile(x, y, flashedTictac);
		}
	}
}

void Maze::tick(const PacVars &vars) noexcept {
	const auto [pX, pY] = currSquare(vars.pacman->getPos());
	const auto info = mazeInfo[pY][pX];
	if ((info == 1 || info == 3 || info == 6) && !depletedGrid[pY][pX]) {
		depletedGrid[pY][pX] = true;
		depleted = true;
		lastDepletedX = pX;
		lastDepletedY = 30 - pY;
	} else {
		depleted = false;
	}
	if (vars.time % 20 >= 10) {
		flashedTictac = true;
	} else {
		flashedTictac = false;
	}
}

bool Maze::canPacGo(Direction dir, glm::vec2 pos) const noexcept {
	const auto [pacCoordX, pacCoordY] = currSquare(pos);		
	// std::cout << "X: " << pacCoordX << "\tY: " << pacCoordY << "\tinfo: " << mazeInfo[pacCoordY][pacCoordX] << '\n';
	if ((pacCoordX <= 0 || pacCoordX >= 27) && (dir == Direction::LEFT || dir == Direction::RIGHT)) {
		return true;
	}
	if (pacCoordX <= 0 || pacCoordX >= 27 || pacCoordY == 0 || pacCoordY == 30) {
		return false;
	}
	if (dir == Direction::UP && (pacPassable(mazeInfo[pacCoordY - 1][pacCoordX]) || fmod(pos.y, 8.f) < 4.f)) {
		return true;
	}
	if (dir == Direction::RIGHT && (pacPassable(mazeInfo[pacCoordY][pacCoordX + 1]) || fmod(pos.x, 8.f) < 4.f)) {
		return true;
	}
	if (dir == Direction::DOWN && (pacPassable(mazeInfo[pacCoordY + 1][pacCoordX]) || fmod(pos.y, 8.f) > 4.f)) {
		return true;
	}
	if (dir == Direction::LEFT && (pacPassable(mazeInfo[pacCoordY][pacCoordX - 1]) || fmod(pos.x, 8.f) > 4.f)) {
		return true;
	}
	return false;
}

bool Maze::pacPassable(int num) const noexcept {
	// std::cout << "can pass? " << ((0 < num && num < 4 || num == 8 || num == 9) ? "yes" : "no") << '\n';
	return 0 < num && num < 4 || num == 6 || num == 8 || num == 9;
}

std::tuple<int, int> Maze::currSquare(glm::vec2 pos) const noexcept {
	const int pacCoordX = gsl::narrow_cast<int>(pos.x) / 8;
	const int pacCoordY = 30 - gsl::narrow_cast<int>((pos.y - 16.f) / 8 + 0.01f);
	return {pacCoordX, pacCoordY};
}

glm::vec2 Maze::currSquareMiddleCoords(glm::vec2 pos) const noexcept {
	auto mod8X = gsl::narrow_cast<int>(pos.x) / 8;
	auto mod8Y = gsl::narrow_cast<int>(pos.y) / 8;
	return glm::vec2(mod8X * 8 + 4.f, mod8Y * 8 + 4.f);
}

bool Maze::isDepleted() const noexcept {
	return depleted;
}

void Maze::switchTile(std::size_t x, std::size_t y, bool switchSquare) noexcept {
	const auto index = x + 28 * y;

	auto *buf {&buffer[index * 4]};
	auto quad {Vertex::getQuad()};

	const float posX {x * 8.f};
	const float posY {y * 8.f};

	const auto add = 28 * 8;
	sTextures[index] = SubTexture {sTextures[index].tex, {posX + add * switchSquare, posY}, {8.f, 8.f}};

	int i {0};
	for (auto &vert : quad) {
		buf[i].texPos = sTextures[index].texQuad[i].texPos;
		i++;
	}
}