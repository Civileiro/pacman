#include "Maze.hpp"

Maze::Maze(Texture *tex) : BatchEntity {4  * 28 * 31 , {0.f, 16.f}} {
	sTextures = std::make_unique<SubTexture[]>(28 * 31);
	//sTextures[0] = SubTexture {tex, {0.f, 0.f}, {224.f, 248.f}};
	for (size_t y {0}; y < 31; y++) {
		for (size_t x {0}; x < 28; x++) {
			const float posX {x * 8.f};
			const float posY {y * 8.f};

			sTextures[x + (y * 28)] = SubTexture {tex, {posX, posY}, {8.f, 8.f}};
		}
	}
}

void Maze::updateBuffer() const noexcept {}

void Maze::tick() noexcept {}

void Maze::initBuffer() const noexcept {

	for (size_t y {0}; y < 31; y++) {
		for (size_t x {0}; x < 28; x++) {
			auto index = x + (y * 28);

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
