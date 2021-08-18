#pragma once

#include <GL/gl3w.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <filesystem>

class Shader {
  private:
	GLuint ID;
	static std::string shaderFolder;

  public:
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
	void checkCompileErrors(const GLuint shader, std::string type) const;
	std::string readShaderFile(std::string_view path) const;
	GLuint createShader(const GLenum GLtype, std::string code, std::string name = "UNDEFINED") const;
};


Shader::Shader(std::string_view vertexFileName, std::string_view fragmentFileName) {


	GLuint vertex = createShader(GL_VERTEX_SHADER, readShaderFile(shaderFolder + '/' + vertexFileName.data()), "VERTEX");
	GLuint fragment = createShader(GL_FRAGMENT_SHADER, readShaderFile(shaderFolder + '/' + fragmentFileName.data()), "FRAGMENT");

	// create program and link shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::checkCompileErrors(const GLuint shader, std::string type) const {
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::string errorMessage {"ERROR::SHADER_COMPILATION_ERROR of type: " + type + "\n" + infoLog +
						  "\n -- --------------------------------------------------- -- "};
			throw std::exception {errorMessage.c_str()};
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::string errorMessage {"ERROR::PROGRAM_LINKING_ERROR of type: " + type + "\n" + infoLog +
						  "\n -- --------------------------------------------------- -- "};
			throw std::exception {errorMessage.c_str()};
		}
	}
}
std::string Shader::readShaderFile(std::string_view path) const {
	std::string code;
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	// read files
	try {
		file.open(path.data());
		std::stringstream shaderStream;
		shaderStream << file.rdbuf();
		file.close();
		code = shaderStream.str();
	} catch (std::ifstream::failure e) {
		std::cout << e.what() << "\n";
		throw std::exception {"ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ"};
	}
	return code;
}
GLuint Shader::createShader(const GLenum GLtype, std::string code, std::string name) const {
	const GLuint shader {glCreateShader(GLtype)};
	const char *codePointer = code.data();
	glShaderSource(shader, 1, &codePointer, NULL);
	glCompileShader(shader);
	checkCompileErrors(shader, name);
	return shader;
}