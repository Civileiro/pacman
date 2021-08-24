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

class Shader {
  private:
	GLuint ID;
	static std::string shaderFolder;

  public:
	Shader() = default;
	Shader(std::string_view vertexFileName, std::string_view fragmentFileName);

	auto getID() const noexcept {
		return ID;
	}
	void use() const noexcept {
		glUseProgram(ID);
	}
	void setBool(std::string_view name, bool value) const noexcept {
		glUniform1i(glGetUniformLocation(ID, name.data()), (int) value);
	}
	void setInt(std::string_view name, int value) const noexcept {
		glUniform1i(glGetUniformLocation(ID, name.data()), value);
	}
	template <size_t vecSize>
	void setIntVec(std::string_view name, const std::array<int, vecSize> values) const noexcept {
		glUniform1iv(glGetUniformLocation(ID, name.data()), vecSize, &values[0]);
	}
	void setFloat(std::string_view name, float value) const noexcept {
		glUniform1f(glGetUniformLocation(ID, name.data()), value);
	}
	void setVec3(std::string_view name, const glm::vec3 &value) const noexcept {
		glUniform3fv(glGetUniformLocation(ID, name.data()), 1, glm::value_ptr(value));
	}
	void setMat3(std::string_view name, const glm::mat3 &value) const noexcept {
		glUniformMatrix3fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE, glm::value_ptr(value));
	}
	void setMat4(std::string_view name, const glm::mat4 &value) const noexcept {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE, glm::value_ptr(value));
	}

  private:
	void checkCompileErrors(const GLuint shader, shaderType type) const;
	std::string readShaderFile(std::string_view path) const;
	GLuint createShader(const GLenum GLtype, std::string_view code, shaderType type = shaderType::UNDEFINED) const;
};

inline Shader::Shader(std::string_view vertexFileName, std::string_view fragmentFileName) {

	const GLuint vertex = createShader(GL_VERTEX_SHADER, readShaderFile(shaderFolder + '/' + vertexFileName.data()), shaderType::VERTEX);
	const GLuint fragment = createShader(GL_FRAGMENT_SHADER, readShaderFile(shaderFolder + '/' + fragmentFileName.data()), shaderType::FRAGMENT);

	// create program and link shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, shaderType::PROGRAM);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

inline void Shader::checkCompileErrors(const GLuint shader, shaderType type) const {
	GLint success;
	GLchar infoLog[1024];
	if (type != shaderType::PROGRAM) {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::stringstream errorMessage;
			errorMessage << "ERROR::SHADER_COMPILATION_ERROR " << static_cast<int>(type) << "\n"
				     << infoLog << "\n -- --------------------------------------------------- -- ";

			throw std::exception {errorMessage.str().c_str()};
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::stringstream errorMessage;
			errorMessage << "ERROR::SHADER_COMPILATION_ERROR " << static_cast<int>(type) << "\n"
				     << infoLog << "\n -- --------------------------------------------------- -- ";

			throw std::exception {errorMessage.str().c_str()};
		}
	}
}
inline std::string Shader::readShaderFile(std::string_view path) const {
	std::string code;
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	// read files
	try {
		file.open(path.data());
		code = std::string {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
		file.close();
	} catch (std::ifstream::failure e) {
		throw std::exception {(std::string {e.what()} + "\nERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\nPath: " + path.data()).c_str()};
	}
	return code;
}
inline GLuint Shader::createShader(const GLenum GLtype, std::string_view code, shaderType type) const {
	const GLuint shader {glCreateShader(GLtype)};
	const char *codePointer = code.data();
	glShaderSource(shader, 1, &codePointer, NULL);
	glCompileShader(shader);
	checkCompileErrors(shader, type);
	return shader;
}