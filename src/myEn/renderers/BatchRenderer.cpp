#include <myEn/renderers/BatchRenderer.hpp>

BatchRenderer::BatchRenderer(const ShaderManager shader, size_t bufferSize)
    : shader {shader},
      bufferSize {bufferSize},
      vertexBuffer {std::make_unique<Vertex[]>(bufferSize)} {

	shader.setIntVec("textures", std::array {0, 1, 2, 3, 4, 5, 6, 7,});

	glGenVertexArrays(1, &VA);
	glGenBuffers(1, &VB);

	glBindVertexArray(VA);
	glBindBuffer(GL_ARRAY_BUFFER, VB);

	glBufferData(GL_ARRAY_BUFFER, bufferSize * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) (offsetof(Vertex, pos)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) (offsetof(Vertex, texPos)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) (offsetof(Vertex, texID)));

	size_t indexCount = gsl::narrow_cast<size_t>(std::ceil(bufferSize * 1.5f));

	auto indices = std::make_unique<GLuint[]>(indexCount);

	int offset {0};
	for (size_t i {0}; i < indexCount; i += 6) {
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;
		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}

	GLuint IB;
	glCreateBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indices.get(), GL_STATIC_DRAW);
}

void BatchRenderer::render() const noexcept {
	//for (int i {4}; i < size; i++) {
	//	//std::cout << "pos" << i << " " << vertexBuffer[i].pos.x << " " << vertexBuffer[i].pos.y << "\n";
	//	std::cout << "tex" << i << " " << vertexBuffer[i].texPos.x << " " << vertexBuffer[i].texPos.y << "\n";
	//}
	shader.use();

	const glm::mat4 proj {glm::ortho(0.f, (float) resWidth, 0.f, (float) resHeight)};
	shader.setMat4("projection", proj);

	int indexCount = gsl::narrow_cast<int>(std::ceil(size * 1.5f));
	glBindVertexArray(VA);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(Vertex), vertexBuffer.get());


	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

}

void BatchRenderer::setResolution(int width, int height) noexcept {
	resWidth = width;
	resHeight = height;
}

void BatchRenderer::setBufferPointer(BatchEntity *entity) noexcept {
	assert(entity->bufferSize + size <= bufferSize);
	entity->buffer = &vertexBuffer[size];
	size += entity->bufferSize;
	entity->initBuffer();
}

void BatchRenderer::clearBatch() noexcept {
	size = 0;
}