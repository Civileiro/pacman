#pragma once

#include <GL/gl3w.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

enum class shaderType { VERTEX, FRAGMENT, PROGRAM, UNDEFINED };

class ShaderManager {
  public:
	ShaderManager() = default;
	ShaderManager(std::string_view vertexFileName, std::string_view fragmentFileName);

	auto getID() const noexcept;
	void use() const noexcept;
	void setBool(std::string_view name, bool value) const noexcept;
	void setInt(std::string_view name, int value) const noexcept;
	template <size_t vecSize>
	void setIntVec(std::string_view name, const std::array<int, vecSize> values) const noexcept;
	void setFloat(std::string_view name, float value) const noexcept;
	void setVec3(std::string_view name, const glm::vec3 &value) const noexcept;
	void setMat3(std::string_view name, const glm::mat3 &value) const noexcept;
	void setMat4(std::string_view name, const glm::mat4 &value) const noexcept;

  private:
	GLuint ID;
	static std::string shaderFolder;

	void checkCompileErrors(const GLuint shader, shaderType type) const;
	std::string readShaderFile(std::string_view path) const;
	GLuint createShader(const GLenum GLtype, std::string_view code, shaderType type = shaderType::UNDEFINED) const;
};

template <size_t vecSize>
void ShaderManager::setIntVec(std::string_view name, const std::array<int, vecSize> values) const noexcept {
	glUniform1iv(glGetUniformLocation(ID, name.data()), vecSize, &values[0]);
}